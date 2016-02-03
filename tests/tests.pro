TEMPLATE = app
CONFIG += testcase

include(../settings.pri)

PRE_TARGETDEPS = ../src/libqtupdater.so
LIBS += -L../src -lqtupdater


SOURCES += main.cpp \
           test_http_fetched.cpp

# Google test
GTESTS_ROOT = $${PWD}/googletest/googletest
INCLUDEPATH += $${GTESTS_ROOT} \
               $${GTESTS_ROOT}/include
SOURCES += $${GTESTS_ROOT}/src/gtest-all.cc
