# coding: utf8
# socketcli.py
# jichi 4/28/2014

if __name__ == '__main__':
  import sys
  sys.path.append('..')

__all__ = ['SocketClient']

from PySide.QtCore import QObject, Signal, QTimer
#from PySide.QtNetwork import QAbstractSocket
from sakurakit.skclass import Q_Q
from sakurakit.skdebug import dprint
import socketio, socketpack

class SocketClient(QObject):

  def __init__(self, parent=None):
    super(SocketClient, self).__init__(parent)
    self.__d = _SocketClient(self)

  connected = Signal()
  disconnected = Signal()
  socketError = Signal()

  dataReceived = Signal(bytearray) # data

  def sendData(self, data, waitTime=0, **kwargs):
    """
    @param  data  str or unicode
    @param* waitTime  int
    @param* pack  bool  whether prepend header to data
    """
    ok = self.__d.writeSocket(data, **kwargs)
    if ok and waitTime:
      ok = self.__d.socket.waitForBytesWritten(waitTime)
    return ok

  def address(self): return self.__d.address # -> str
  def setAddress(self, v): self.__d.address = v

  def port(self): return self.__d.port # -> int
  def setPort(self, v): self.__d.port = v

  def isActive(self): # -> bool, is connected
    s = self.__d.socket
    return bool(s) and s.state() == s.ConnectedState

  def isReady(self): # -> bool, is connected or disconnected instead of connecting or uninitialized
    s = self.__d.socket
    return bool(s) and s.state() in (s.ConnectedState, s.UnconnectedState)

  def start(self): self.__d.start()
  def stop(self): self.__d.stop()

  #def waitForReady(self):
  #  s = self.__d.socket
  #  if s and s.state() not in (s.ConnectedState, s.UnconnectedState):
  #    from PySide.QtCore import QEventLoop
  #    loop = QEventLoop()
  #    s.stateChanged.connect(loop.quit)
  #    s.error.connect(loop.quit)
  #    loop.exec_();
  #    while s.state() in (s.HostLookupState, s.ConnectingState):
  #      loop.exec_()

  # QAbstractSocket default wait time is 30 seconds
  def waitForConnected(self, interval=30000): # -> bool
    return bool(self.__d.socket) and self.__d.socket.waitForConnected(interval)
  def waitForDisconnected(self, interval=30000): # -> bool
    return bool(self.__d.socket) and self.__d.socket.waitForDisconnected(interval)
  def waitForBytesWritten(self, interval=30000): # -> bool
    return bool(self.__d.socket) and self.__d.socket.waitForBytesWritten(interval)
  def waitForReadyRead(self, interval=30000): # -> bool
    return bool(self.__d.socket) and self.__d.socket.waitForReadyRead(interval)

  def dumpSocketInfo(self): # print the status of the socket. for debug only
    self.__d.dumpSocketInfo()

@Q_Q
class _SocketClient(object):
  def __init__(self, q):
    self.encoding = 'utf8'
    self.address = '127.0.0.1' # host name without http prefix
    self.port = 0 # int
    self.socket = None # # QTcpSocket

  def _createSocket(self):
    from PySide.QtNetwork import QTcpSocket
    q = self.q
    ret = QTcpSocket(q)
    socketio.initsocket(ret)
    ret.error.connect(q.socketError)
    ret.connected.connect(q.connected)
    ret.disconnected.connect(q.disconnected)
    ret.readyRead.connect(self.readSocket)
    return ret

  def start(self):
    from PySide.QtNetwork import QHostAddress
    if not self.socket:
      self.socket = self._createSocket()
    self.socket.connectToHost(QHostAddress(self.address), self.port)
    dprint("pass")

  def stop(self):
    if self.socket and self.socket.isOpen():
      self.socket.close()
      dprint("pass")

  def readSocket(self):
    s = self.socket
    if s:
      while s.bytesAvailable():
        data = socketio.readsocket(s)
        if data == None:
          break
        else:
          self.q.dataReceived.emit(data)

  def writeSocket(self, data, pack=True):
    if not self.socket:
      return False;
    if isinstance(data, unicode):
      data = data.encode(self.encoding, errors='ignore')
    return socketio.writesocket(data, self.socket, pack=pack)

  def dumpSocketInfo(self): # for debug only
    if self.socket:
      dprint("localAddress = %s" % self.socket.localAddress())
      dprint("localPort = %s" % self.socket.localPort())
      dprint("peerAddress = %s" % self.socket.peerAddress())
      dprint("peerPort =  %s" % self.socket.peerPort())
      dprint("state = %s" % self.socket.state())
      dprint("error = %s" % self.socket.errorString())

# Cached

class BufferedSocketClient(SocketClient):

  def __init__(self, parent=None):
    super(BufferedSocketClient, self).__init__(parent)
    self.__d = _BufferedSocketClient(self)

  def sendDataLater(self, data, interval=200, waitTime=0):
    self.__d.sendBuffer += socketpack.packdata(data)
    self.__d.sendTimer.start(interval)
    self.__d.sendWaitTime = waitTime

  def flushSendBuffer(self): self.__d.flushSendBuffer()

class _BufferedSocketClient(object):
  def __init__(self, q):
    self.q_sendData = q.sendData

    self.sendBuffer = '' # str
    self.sendWaitTime = 0 # int

    self.sendTimer = t = QTimer(q)
    t.setSingleShot(True)
    t.timeout.connect(self.flushSendBuffer)

  def flushSendBuffer(self):
    if self.sendTimer.isActive():
      self.sendTimer.stop()
    if self.sendBuffer:
      self.q_sendData(self.sendBuffer, waitTime=self.sendWaitTime, pack=False)
      self.sendBuffer = ''

if __name__ == '__main__':
  import sys
  from PySide.QtCore import QCoreApplication
  app =  QCoreApplication(sys.argv)
  #c = SocketClient()
  c = BufferedSocketClient()
  c.setPort(6002)
  def f(data):
    print data, type(data), len(data)
    app.quit()
  c.dataReceived.connect(f)
  c.start()
  #c.waitForReady()
  c.waitForConnected()

  #t = "hello"
  #t = u"こんにちは"

  interval = 200

  t = '0' * 100
  #print t
  c.sendDataLater(t)
  t = '1' * 100
  #print t
  c.sendDataLater(t)
  t = '2' * 100
  #print t
  c.sendDataLater(t)
  t = '3' * 100
  #print t
  c.sendDataLater(t)
  t = '4' * 100
  #print t
  c.sendDataLater(t)
  t = '5' * 100
  #print t
  c.sendDataLater(t)
  print c.isActive()

  #t = '1' * 100
  #ok = c.sendData(t)
  #print ok

  c.disconnected.connect(app.quit)

  #c.dumpSocketInfo()

  sys.exit(app.exec_())

# EOF
