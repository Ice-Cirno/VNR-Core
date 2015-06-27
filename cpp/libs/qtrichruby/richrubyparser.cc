// richrubyparser.cc
// 6/25/2015 jichi
#include "qtrichruby/richrubyparser.h"
#include <QtCore/QStringList>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <functional>
#include<QDebug>
/** Private class */

class RichRubyParserPrivate
{
public:
  wchar_t openChar, closeChar, splitChar;

  RichRubyParserPrivate()
    : openChar('{'), closeChar('}'), splitChar('|') {}

  static QString partition(const QString &text, int width, const QFontMetrics &font, bool wordWrap, int maximumWordSize);

  // return if stop iteration. pos it the parsed offset
  typedef std::function<bool (const QString &rb, const QString &rt, int pos)> ruby_fun_t;
  void iterRuby(const QString &text,  const ruby_fun_t &fun) const;

  void removeRuby(QString &text) const;

  bool containsRuby(const QString &text) const
  {
    int pos = text.indexOf(openChar);
    return pos != -1
        && (pos = text.indexOf(splitChar, pos)) != -1
        && (pos = text.indexOf(closeChar, pos)) != -1;
  }

  QString createRuby(const QString &rb, const QString &rt) const
  {
    return QString()
        .append(openChar)
        .append(rb)
        .append(splitChar)
        .append(rt)
        .append(closeChar);
  }
};

QString RichRubyParserPrivate::partition(const QString &text, int width, const QFontMetrics &font, bool wordWrap, int maximumWordSize)
{
  QString ret;
  if (width <= 0 || text.isEmpty())
    return ret;
  int retWidth = 0;
  int spacePos = -1;
  for (int pos = 0; pos < text.size(); pos++) {
    const QChar &ch = text[pos];
    if (wordWrap && ch.isSpace())
      spacePos = pos;
    retWidth += font.width(ch);
    if (retWidth > width) {
      if (wordWrap && spacePos >= 0 && spacePos < pos && pos - spacePos < maximumWordSize)
        ret = ret.left(spacePos + 1);
      break;
    }
    ret.push_back(ch);
  }
  return ret;
}

void RichRubyParserPrivate::iterRuby(const QString &text,  const ruby_fun_t &fun) const
{
  QString rb, rt, plainText;
  bool rubyOpenFound = false,
       rubySplitFound = false;

  auto cancel = [&]() {
    if (rubyOpenFound) {
      rubyOpenFound = false;
      plainText.push_back(openChar);
    } if (!rb.isEmpty()) {
      plainText.append(rb);
      rb.clear();
    }
    if (rubySplitFound) {
      rubySplitFound = false;
      plainText.push_back(splitChar);
    }
    if (!rt.isEmpty()) {
      //plainText.push_back(closeChar);
      plainText.append(rt);
      rt.clear();
    }
  };

  int pos = 0;
  for (; pos < text.size(); pos++) {
    const QChar &ch = text[pos];
    auto u = ch.unicode();
    if (u == openChar) {
      if (rubyOpenFound) // error
        cancel();
      if (!plainText.isEmpty()) {
        if (!fun(plainText, QString(), pos))
          return;
        plainText.clear();
      }
      rubyOpenFound = true;
    } else if (u == splitChar) {
      if (!rubyOpenFound) // error
        plainText.push_back(ch);
      else if (rb.isEmpty()) { // error, do not allow having only rt
        cancel();
        plainText.push_back(ch);
      } else if (rubySplitFound) // error
        rt.push_back(ch);
      else
        rubySplitFound = true;
    } else if (u == closeChar) {
      if (!rubyOpenFound) // error
        plainText.push_back(ch);
      else if (rt.isEmpty() || rb.isEmpty()) { // error, do not allow having only rb or rt
        cancel();
        plainText.push_back(ch);
      } else {
        if (!fun(rb, rt, pos + 1))
          return;
        rubySplitFound = rubyOpenFound = false;
        rb.clear();
        rt.clear();
      }
    } else
      (!rubyOpenFound ? plainText : rubySplitFound ? rt : rb).push_back(ch);
  }
  if (!rb.isEmpty() && !rt.isEmpty())
    fun(rb, rt, pos);
  else
    cancel();
  if (!plainText.isEmpty())
    fun(plainText, QString(), pos);
}

void RichRubyParserPrivate::removeRuby(QString &ret) const
{
  for (int pos = ret.indexOf(openChar); pos != -1; pos = ret.indexOf(openChar, pos)) {
    int splitPos = ret.indexOf(splitChar, pos);
    if (splitPos == -1)
      return;
    int closePos = ret.indexOf(closeChar, splitPos);
    if (closePos == -1)
      return;
    ret.remove(closePos, 1);
    ret.remove(pos, splitPos - pos + 1);
    pos += closePos - splitPos - 1;
  }
  return;
}

/** Public class */

RichRubyParser::RichRubyParser() : d_(new D) {}
RichRubyParser::~RichRubyParser() { delete d_; }

int RichRubyParser::openChar() const { return d_->openChar; }
void RichRubyParser::setOpenChar(int v) { d_->openChar = v; }

int RichRubyParser::closeChar() const { return d_->closeChar; }
void RichRubyParser::setCloseChar(int v) { d_->closeChar = v; }

int RichRubyParser::splitChar() const { return d_->splitChar; }
void RichRubyParser::setSplitChar(int v) { d_->splitChar = v; }

bool RichRubyParser::containsRuby(const QString &text) const
{ return d_->containsRuby(text); }

QString RichRubyParser::createRuby(const QString &rb, const QString &rt) const
{ return d_->createRuby(rb, rt); }

QString RichRubyParser::removeRuby(const QString &text) const
{
  if (!containsRuby((text)))
    return text;
  QString ret = text;
  d_->removeRuby(ret);
  return ret;
}

QString RichRubyParser::renderTable(const QString &text, int width, const QFontMetrics &rbFont, const QFontMetrics &rtFont, int cellSpace, bool wordWrap) const
{
  if (!containsRuby((text)))
    return text;

  QString ret;
  QStringList rbList,
              rtList;
  int maximumWordSize = width / 4 + 1;
  int tableWidth = 0;

  const int rbMinCharWidth = rbFont.width(' ') / 4;
            //rtMinCharWidth = rtFont.width(' ') / 4;

  width -= rbMinCharWidth + cellSpace;
  if (width < 0)
    width = 0;

  auto reduce = [&]() {
    bool rbEmpty = true,
         rtEmpty = true;
    if (!rbList.isEmpty())
      foreach (const QString &it, rbList)
        if (!it.isEmpty()) {
          rbEmpty = false;
          break;
        }
    if (!rtList.isEmpty())
      foreach (const QString &it, rtList)
        if (!it.isEmpty()) {
          rtEmpty = false;
          break;
        }
    if (!rbEmpty || !rtEmpty) {
      if (rbEmpty)
        ret.append("<div class='rt'>")
           .append(rtList.join(QString()))
           .append("</div>");
      else if (rtEmpty)
        ret.append("<div class='rb'>")
           .append(rbList.join(QString()))
           .append("</div>");
      else {
        QString rbtd,
                rttd;
        foreach (const QString &it, rbList)
          if (it.isEmpty())
            rbtd.append("<td/>");
          else
            rbtd.append("<td align='center'>")
                .append(it)
                .append("</td>");
        foreach (const QString &it, rtList)
          if (it.isEmpty())
            rttd.append("<td/>");
          else
            rttd.append("<td align='center'>")
                .append(it)
                .append("</td>");
        ret.append("<table>")
           .append("<tr class='rt' valigh='bottom'>").append(rttd).append("</tr>")
           .append("<tr class='rb'>").append(rbtd).append("</tr>")
           .append("</table>");
      }
    }

    rbList.clear();
    rtList.clear();
    tableWidth = 0;
  };
  d_->iterRuby(text, [&](const QString &_rb, const QString &rt, int pos) -> bool {
    QString rb = _rb;
    const bool atLast = pos == text.size();
    if (rt.isEmpty() && ret.isEmpty() && atLast && rb == text) {
      ret = text;
      return false;
    }
    int cellWidth =  qMax(
      rb.isEmpty() ? 0 : rbFont.width(rb),
      rt.isEmpty() ? 0 : rtFont.width(rt)
    );
    if (rt.isEmpty() && rb.size() > 1
        && width && tableWidth < width && tableWidth + cellWidth > width) { // split very long text
      QString left = D::partition(rb, width + rbMinCharWidth - tableWidth, rbFont, wordWrap, maximumWordSize);
      if (!left.isEmpty()) {
        tableWidth += rbFont.width(left);
        rb = rb.mid(left.size());
        cellWidth = rb.isEmpty() ? 0 : rbFont.width(rb);
        rbList.append(left);
        rtList.append(QString());
        reduce();
      }
    }
    if (tableWidth > 0 && width && tableWidth + cellWidth > width // reduce table here
        && (!rbList.isEmpty() || !rtList.isEmpty()))
      reduce();
    if (rt.isEmpty() && width && !tableWidth) {
      if (atLast) {
        rbList.append(rb);
        rtList.append(QString());
        return false;
      }

      while (rb.size() > 1 && cellWidth > width) { // split very long text
        QString left = D::partition(rb, width + rbMinCharWidth - tableWidth, rbFont, wordWrap, maximumWordSize);
        if (left.isEmpty())
          break;
        else {
          tableWidth += rbFont.width(left);
          rb = rb.mid(left.size());
          cellWidth = rb.isEmpty() ? 0 : rbFont.width(rb);
          rbList.append(left);
          rtList.append(QString());
          reduce();
        }
      }
    }
    tableWidth += cellWidth + cellSpace;
    rbList.append(rb);
    rtList.append(rt);
    return true;
  });
  if (!rbList.isEmpty() || !rtList.isEmpty())
    reduce();
  return ret;
}

// EOF
