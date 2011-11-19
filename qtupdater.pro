TEMPLATE = app
CONFIG  += qt warn_on
QT = core network script

CONFIG(debug):QT += gui scripttools

SOURCES += main.cpp \
    updater.cpp \
    fetchers/filefetcher.cpp \
    fetchers/smartfetcher.cpp

HEADERS += \
    updater.h \
    fetchers/ifetcher.h \
    fetchers/filefetcher.h \
    updaterexception.h \
    fetchers/smartfetcher.h

OTHER_FILES += README \
               INSTALL \
               examples/simple.js


exists(.gitignore) {
    OTHER_FILES += .gitignore
}
