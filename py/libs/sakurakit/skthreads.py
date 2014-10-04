# coding: utf8
# skthreads.py
# 10/29/2012 jichi
__all__ = 'runsync', 'runasync', 'runasynclater'

from functools import partial
from PySide.QtCore import Signal, Qt, QObject, QRunnable,QThreadPool
from skdebug import derror
import skevents

## Run async in parallel ##

class _SkRunnableFunction(QRunnable):
  def __init__(self, trigger=None):
    super(_SkRunnableFunction, self).__init__()
    self.trigger = trigger

  def run(self):
    """@reimp @public"""
    try: self.trigger()
    except Exception, e: derror(e)

def runasync(func):
  """Run in another thread"""
  r = _SkRunnableFunction(func)
  QThreadPool.globalInstance().start(r)

def runasynclater(func, interval=0):
  """Run in another thread later after interval"""
  skevents.runlater(partial(
      runasync, func),
      interval)

## Run sync in parallel ##

#class SkReturnObject(object):
#  def __init__(self, value=None):
#    self.value = value
#
#  def assign(self, that):
#    """
#    @param  that  SkReturnObject
#    """
#    self.value = that.value

class _SkRunnableFunctionWithReturn(QObject, QRunnable):
  def __init__(self, trigger=None):
    #super(_SkRunnableFunctionWithReturn, self).__init__(parent)
    QObject.__init__(self) # no parent!
    QRunnable.__init__(self)
    self.trigger = trigger
    self.value = None # return value

  finished = Signal()

  def run(self):
    """@reimp @public"""
    try: self.value = self.trigger()
    except Exception, e: derror(e)
    self.finished.emit()

def runsync(func, parent=None, abortSignal=None):
  """Run in another thread, and then block and wait for return result
  @param  func  function with return value
  @param  parent  QObject or None  parent of the blocking event loop
  @param  abortSignal  Signal  control whether to abort the blocked event loop
  @return  the value returned from function
  """
  r = _SkRunnableFunctionWithReturn(func) # no parent
  skevents.runlater(partial(
      QThreadPool.globalInstance().start, r))
  skevents.waitsignal(r.finished,
      abortSignal=abortSignal,
      type=Qt.QueuedConnection, parent=parent)
  return r.value

# EOF
