#ifndef _SOCKETSVC_SOCKETPACK_H
#define _SOCKETSVC_SOCKETPACK_H

// socketpack.h
// 4/29/2014 jichi
//
// This class must be consistent with socketsvc/socketpack.py
#include "qtsocketsvc/socketdef.h"
#include <QtCore/QStringList>

//QTSS_BEGIN_NAMESPACE

namespace SocketService {

enum { // number of bytes of an int32 number
  Int32Size = 4,
  UInt32Size = Int32Size
};

inline QByteArray packUInt32(quint32 value)
{
  enum { size = 4 };
  quint8 bytes[size] = {
    static_cast<quint8>( value >> 24),
    static_cast<quint8>((value >> 16) & 0xff),
    static_cast<quint8>((value >> 8)  & 0xff),
    static_cast<quint8>( value        & 0xff)
  };
  return QByteArray(reinterpret_cast<char *>(bytes), size);
}

inline quint32 unpackUInt32(const QByteArray &data, int offset = 0)
{
  // QByteArray by default is an array of char, which is signed char. quint8 is unsigned.
  return data.size() < 4 ? 0 :
        (static_cast<quint32>(data[offset])     << 24)
      | (static_cast<quint32>(data[offset + 1]) << 16)
      | (static_cast<quint32>(data[offset + 2]) <<  8)
      |  static_cast<quint32>(data[offset + 3]);
}

// Force using utf8 encoding
QByteArray packStringList(const QStringList &l, const char *encoding = SOCKET_SERVICE_ENCODING);
QStringList unpackStringList(const QByteArray &data, const char *encoding = SOCKET_SERVICE_ENCODING);

} // SocketService

//QTSS_END_NAMESPACE

#endif // _SOCKETSVC_SOCKETPACK_H
