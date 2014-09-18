TEMPLATE = app

LIBS   += -lz -lpng

RESOURCES = resource.qrc

HEADERS = src/mainwindow.h \
          src/table.h

SOURCES = src/table.cpp \
          src/mainwindow.cpp \
          src/main.cpp

TARGET = tweakpng

QMAKE_CLEAN += $(TARGET) $(QMAKE_TARGET)

