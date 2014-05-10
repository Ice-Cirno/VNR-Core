// embedmanager.cc
// 4/26/2014 jichi

#include "config.h"
#include "embed/embedmemory.h"
#include <QtCore/QCoreApplication>

#define DEBUG "embedmemory"
#include "sakurakit/skdebug.h"

// Helpers

namespace { // unamed

QString getMemoryKey()
{
  qint64 pid = QCoreApplication::applicationPid();
  return QString(VNRAGENT_MEMORY_KEY).arg(QString::number(pid));
}

} // unnamed namespace

// Construction

EmbedMemory::EmbedMemory(QObject *parent) : Base(::getMemoryKey(), parent) {}
EmbedMemory::~EmbedMemory() {}

// Management

bool EmbedMemory::create()
{
  enum { ReadOnly = 1 };
  bool ok = Base::create(VNRAGENT_MEMORY_SIZE, ReadOnly);
  DOUT("ret =" << ok);
  return ok;
}

// EOF