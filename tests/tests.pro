TEMPLATE = app
CONFIG += testcase

SOURCES += main.cpp


GTESTS_SRC_ROOT = /usr/src/gtest/
INCLUDEPATH += $${GTESTS_SRC_ROOT}
SOURCES += $${GTESTS_SRC_ROOT}/src/gtest-all.cc
