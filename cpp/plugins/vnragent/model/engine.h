#pragma once

// engine.h
// 4/20/2014 jichi

#include "sakurakit/skglobal.h"
#include <QtCore/QObject>

class AbstractEnginePrivate;
class AbstractEngine
{
  //Q_OBJECT
  SK_CLASS(AbstractEngine)
  SK_DECLARE_PRIVATE(AbstractEnginePrivate)
  SK_DISABLE_COPY(AbstractEngine)

public:
  static Self *instance();

  AbstractEngine(const char *name, const char *encoding);
  virtual ~AbstractEngine();

  const char *name() const;
  const char *encoding() const;

  virtual bool inject() = 0;

  //static bool isEnabled();
  //static void setEnabled(bool t);

//signals:
//  // context is opaque, and the receiver of this signal is responsible to release the context
//  void textReceived(const QString &text, qint64 hash, int role, void *context);
public:
  virtual void drawText(const QString &text, const void *context) = 0;
  virtual void releaseContext(void *context) = 0;

protected:
  QString dispatchText(const QByteArray &data, int role, void *context) const;
};

// EOF
