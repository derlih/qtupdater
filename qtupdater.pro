TEMPLATE = app
CONFIG  += qt warn_on release
QT = core

CONFIG(debug):QT += gui

SOURCES += main.cpp

OTHER_FILES += README \
               INSTALL
