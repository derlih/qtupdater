TEMPLATE = app
CONFIG += testcase

SOURCES += main.cpp

# Google test
#TODO: Remove default path
GTESTS_SRC_ROOT = /usr/src/gtest/
INCLUDEPATH += $${GTESTS_ROOT}
SOURCES += $${GTESTS_ROOT}/src/gtest-all.cc
