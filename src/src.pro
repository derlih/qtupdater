TEMPLATE = lib
TARGET = qtupdater
CONFIG  += shared qt warn_on
QT = core network script

include(../settings.pri)

CONFIG(debug, debug|release){
    QT += widgets scripttools
    DEFINES += USE_SCRIPT_DEBUGGER
}

SOURCES += main.cpp \
           fetchers/http_fetcher.cpp

HEADERS += fetchers/fetcher.hpp \
           fetcher_exceptions.hpp \
           fetchers/http_fetcher.hpp
