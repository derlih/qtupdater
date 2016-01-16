TEMPLATE = app
CONFIG  += qt warn_on
QT = core network script

CONFIG(debug, debug|release){
    QT += widgets scripttools
    DEFINES += USE_SCRIPT_DEBUGGER
}

SOURCES += main.cpp \
    updater.cpp \
    fetchers/filefetcher.cpp \
    fetchers/smartfetcher.cpp \
    scripthelpers/scriptconsole.cpp \
    scripthelpers/helperfunctions.cpp \
    fetchers/httpfetcher.cpp

HEADERS += \
    updater.h \
    fetchers/ifetcher.h \
    fetchers/filefetcher.h \
    updaterexception.h \
    fetchers/smartfetcher.h \
    scripthelpers/scriptconsole.h \
    scripthelpers/helperfunctions.h \
    fetchers/httpfetcher.h

OTHER_FILES += README \
               INSTALL \
               examples/simple.js


exists(.gitignore) {
    OTHER_FILES += .gitignore
}
