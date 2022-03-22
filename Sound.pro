TEMPLATE = app
TARGET = Sound

CONFIG += console
CONFIG -= qt

INCLUDEPATH += .
INCLUDEPATH += ./include

mac {
    LIBS += -framework OpenAL
}

win32 {
    INCLUDEPATH += $(OPENAL_HOME)\\include\\AL
    LIBS *= $(OPENAL_HOME)\\libs\\Win64\\libOpenAL32.dll.a
}

# Input
HEADERS += \
    include/vector3.h \
    include/wavfilehandler.h \
    include/soundmanager.h \
    include/soundsource.h


SOURCES += \
    src/vector3.cpp \
    src/main.cpp \
    src/wavfilehandler.cpp \
    src/soundsource.cpp \
    src/soundmanager.cpp
