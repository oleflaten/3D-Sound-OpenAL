TEMPLATE = app
TARGET = Sound

CONFIG += console
CONFIG -= qt

INCLUDEPATH += .
INCLUDEPATH += ./include

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

#Set up dependencies
mac {
    LIBS += -framework OpenAL
}

win32 {
    INCLUDEPATH += ./openal/include/AL
    LIBS += $$PWD/openal/libs/OpenAL32.lib

# Copy required DLL to output directory
        CONFIG(debug, debug|release) {
            OpenAL32.commands = copy /Y \"$$PWD\\openal\\dlls\\OpenAL32.dll\" debug
            OpenAL32.target = debug/OpenAL32.dll

            QMAKE_EXTRA_TARGETS += OpenAL32
            PRE_TARGETDEPS += debug/OpenAL32.dll
        } else:CONFIG(release, debug|release) {
            OpenAL32.commands = copy /Y \"$$PWD\\openal\\dlls\\OpenAL32.dll\" release
            OpenAL32.target = release/OpenAL32.dll

            QMAKE_EXTRA_TARGETS += OpenAL32
            PRE_TARGETDEPS += release/OpenAL32.dll release/OpenAL32.dll
        } else {
            error(Unknown set of dependencies.)
        }
}
