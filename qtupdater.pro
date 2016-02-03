TEMPLATE = app
CONFIG  += qt warn_on
QT = core network script

CONFIG(debug, debug|release){
    QT += widgets scripttools
    DEFINES += USE_SCRIPT_DEBUGGER
}

SOURCES += main.cpp

#HEADERS += \

OTHER_FILES += README \
               INSTALL

exists(.gitignore) {
    OTHER_FILES += .gitignore
}
