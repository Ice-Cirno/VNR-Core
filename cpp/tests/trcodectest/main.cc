// main.cc
// 9/20/2014 jichi
#include "trcodec/trcodec.h"
#include <QtCore>

int main()
{
  qDebug() << "enter";

  wchar_t ws[] = L"【爽】「悠真くんを攻略すれば２１０円か。なるほどなぁ…」";
  //wchar_t ws[] = L"【綾波レイ】「こんにちは、DELETE世界！」";
  std::wstring text = ws;

  std::wstring path;
  //path = L"../cpp/libs/trscript/example.txt";
  //path = L"/Users/jichi/stream/Caches/tmp/reader/dict/ja-zhs/trans_input.txt";
  path = L"/Users/jichi/opt/stream/Library/Frameworks/Sakura/cpp/libs/trcodec/example.txt";
  //path = L"/Users/jichi/stream/Caches/tmp/reader/dict/ja/game.txt";
  //path = L"../../../../Caches/tmp/reader/dict/zhs/test.txt";
  //path = L"/Users/jichi/tmp/escape_input.txt";

  TranslationCodec m;
  m.loadScript(path);
  qDebug() << m.size();

  if (!m.isEmpty()) {
    qDebug() << QString::fromStdWString(text);
    text = m.encode(text);
    qDebug() << QString::fromStdWString(text);

    text = m.decode(text);
    qDebug() << QString::fromStdWString(text);
  }

  qDebug() << "leave";
  return 0;
}

// EOF
