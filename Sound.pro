TEMPLATE = app
TARGET = Sound

CONFIG += console
CONFIG -= qt

INCLUDEPATH += . \
    ./include

HEADERS += \
    include/soundmanager.h \
    include/soundsource.h \
    include/vector3.h \
    include/wavfilereader.h

SOURCES += \
    src/main.cpp \
    src/soundsource.cpp \
    src/soundmanager.cpp \
    src/vector3.cpp \
    src/wavfilereader.cpp

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
