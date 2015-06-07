# vnragent.pro
# 1/22/2013 jichi

CONFIG += noqtgui dll
include(../../../config.pri)
#include($$LIBDIR/detoursutil/detoursutil.pri)
include($$LIBDIR/disasm/disasm.pri)
include($$LIBDIR/libqxt/libqxt.pri)
include($$LIBDIR/memdbg/memdbg.pri)
#include($$LIBDIR/mhook/mhook.pri)
#include($$LIBDIR/mhook-disasm/mhook-disasm.pri)
include($$LIBDIR/ntinspect/ntinspect.pri)
#include($$LIBDIR/qtembedapp/qtembedapp.pri) # needed by app runner
include($$LIBDIR/qtembedplugin/qtembedplugin.pri)
#include($$LIBDIR/qtmetacall/qtmetacall.pri)
include($$LIBDIR/qtjson/qtjson.pri)
include($$LIBDIR/qtdyncodec/qtdyncodec.pri)
include($$LIBDIR/qtsocketsvc/qtsocketpack.pri)
include($$LIBDIR/qtsocketsvc/qtsocketpipe.pri)
include($$LIBDIR/qtsocketsvc/qtlocalcli.pri)
#include($$LIBDIR/qtsocketsvc/qttcpcli.pri)
include($$LIBDIR/sakurakit/sakurakit.pri)
include($$LIBDIR/vnrsharedmemory/vnrsharedmemory.pri)
include($$LIBDIR/windbg/windbg.pri)
#include($$LIBDIR/winevent/winevent.pri)
include($$LIBDIR/winkey/winkey.pri)
include($$LIBDIR/winhook/winhook.pri)
include($$LIBDIR/winiter/winiter.pri)
include($$LIBDIR/winquery/winquery.pri)
#include($$LIBDIR/wintimer/wintimer.pri)
include($$LIBDIR/winmutex/winmutex.pri)
include($$LIBDIR/winsinglemutex/winsinglemutex.pri)

#include($$LIBDIR/vnragent/vnragent.pri)

# Services
#HEADERS += $$SERVICEDIR/reader/metacall.h

## Libraries

#CONFIG  += noqt
QT      += core network
QT      -= gui

#INCLUDEPATH += $$D3D_HOME/include
#LIBS    += -ld3d9 -L$$D3D_HOME/lib/x86

#LIBS    += -lkernel32
#LIBS    += -luser32 -lpsapi
#LIBS    += -ladvapi32   # needed by RegQueryValueEx
LIBS    += -lgdi32      # needed by game engines
LIBS    += -lshell32    # needed by get system path

## Sources

TEMPLATE = lib
TARGET  = vnragent

HEADERS += \
  driver/maindriver.h \
  driver/maindriver_p.h \
  driver/rpcclient.h \
  driver/rpcclient_p.h \
  driver/settings.h \
  embed/embeddriver.h \
  embed/embedmanager.h \
  embed/embedmemory.h \
  engine/enginecontroller.h \
  engine/enginedef.h \
  engine/enginefactory.h \
  engine/enginehash.h \
  engine/enginemodel.h \
  engine/enginesettings.h \
  engine/engineutil.h \
  hijack/hijackdriver.h \
  hijack/hijackfuns.h \
  hijack/hijackmanager.h \
  hijack/hijackmodule.h \
  hijack/hijackmodule_p.h \
  hijack/hijackhelper.h \
  hijack/hijacksettings.h \
  window/windowdriver.h \
  window/windowdriver_p.h \
  window/windowhash.h \
  window/windowmanager.h \
  util/codepage.h \
  util/dyncodec.h \
  util/location.h \
  util/msghandler.h \
  util/textutil.h \
  config.h \
  debug.h \
  growl.h \
  loader.h

SOURCES += \
  driver/maindriver.cc \
  driver/rpcclient.cc \
  driver/settings.cc \
  embed/embeddriver.cc \
  embed/embedmanager.cc \
  embed/embedmemory.cc \
  engine/enginecontroller.cc \
  engine/enginefactory.cc \
  engine/engineutil.cc \
  hijack/hijackdriver.cc \
  hijack/hijackfuns.cc \
  hijack/hijackmanager.cc \
  hijack/hijackmodule.cc \
  hijack/hijackmodule_kernel32.cc \
  hijack/hijackmodule_user32.cc \
  hijack/hijackhelper.cc \
  window/windowdriver.cc \
  window/windowdriver_p.cc \
  window/windowmanager.cc \
  util/codepage.cc \
  util/dyncodec.cc \
  util/location.cc \
  util/msghandler.cc \
  util/textutil.cc \
  growl.cc \
  loader.cc \
  main.cc

# Engine models
HEADERS += \
  engine/model/age.h \
  engine/model/aoi.h \
  engine/model/bgi.h \
  engine/model/elf.h \
  engine/model/system4.h \
  engine/model/siglus.h
  #engine/model/circus.h
  #engine/model/elf.h
  #engine/model/eushully.h \
  #engine/model/majiro.h \
  #engine/model/sideb.h \
  ##engine/model/nexas.h
  #engine/model/rejet.h
  #engine/model/test.h
SOURCES += \
  engine/model/age.cc \
  engine/model/aoi.cc \
  engine/model/bgi.cc \
  engine/model/elf.cc \
  engine/model/system4.cc \
  engine/model/siglus.cc
  #engine/model/circus.cc
  #engine/model/elf.cc
  #engine/model/eushully.cc
  #engine/model/majiro.cc
  #engine/model/sideb.cc
  #engine/model/nexas.cc
  #engine/model/rejet.cc
  #engine/model/test.cc

#!wince*: LIBS += -lshell32
#RC_FILE += vnragent.rc

OTHER_FILES += vnragent.rc

# EOF
