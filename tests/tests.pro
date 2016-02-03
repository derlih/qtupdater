TEMPLATE = app
CONFIG += testcase

SOURCES += main.cpp

# Google test
GTESTS_ROOT = $${PWD}/googletest/googletest
INCLUDEPATH += $${GTESTS_ROOT} \
               $${GTESTS_ROOT}/include
SOURCES += $${GTESTS_ROOT}/src/gtest-all.cc
