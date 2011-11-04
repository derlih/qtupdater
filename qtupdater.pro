TEMPLATE = app
CONFIG  += qt warn_on release
QT = core network

CONFIG(debug):QT += gui

SOURCES += main.cpp \
    updater.cpp \
    fetchers/filefetcher.cpp \
    fetchers/smartfetcher.cpp

OTHER_FILES += README \
               INSTALL

HEADERS += \
    updater.h \
    fetchers/ifetcher.h \
    fetchers/filefetcher.h \
    updaterexception.h \
    fetchers/smartfetcher.h
