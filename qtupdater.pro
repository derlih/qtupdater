TEMPLATE = app
CONFIG  += qt warn_on release
QT = core network

CONFIG(debug):QT += gui

SOURCES += main.cpp \
    updater.cpp

OTHER_FILES += README \
               INSTALL

HEADERS += \
    updater.h
