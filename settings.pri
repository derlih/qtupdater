win32 {
      QMAKE_CXXFLAGS += /WX
}
else {
     QMAKE_CXXFLAGS += -Werror
}
