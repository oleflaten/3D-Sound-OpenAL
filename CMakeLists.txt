cmake_minimum_required(VERSION 3.16)

project(Sound LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    include/soundmanager.h
    include/soundsource.h
    include/vector3.h
    include/wavfilereader.h
)

set(SOURCES
    src/main.cpp
    src/soundmanager.cpp
    src/soundsource.cpp
    src/vector3.cpp
    src/wavfilereader.cpp
)

add_executable(Sound ${SOURCES} ${HEADERS})

# Must be after add_executable()
# This makes it possible to include the projects .h files without the folder name
target_include_directories(Sound PRIVATE include)


# Adding External library:
# ----------------
# Using Windows environment variable:
# Add include directory
#target_include_directories(Sound PRIVATE $ENV{OPENAL_HOME}/include)
# Add lib directory
#target_link_libraries(Sound PRIVATE $ENV{OPENAL_HOME}/libs/Win64/libOpenAL32.dll.a) # could be OpenAL32.lib)

#Using the version that is included with the project:
# Add include directory
target_include_directories(Sound PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/openal/include)
# Add lib directory
target_link_libraries(Sound PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/openal/lib/OpenAL32.lib)

# ----------------


# Copy the DLL after build
# This makes the .exe use the correct .dll from the library we compile to
# (the "COMMAND echo" only works on Windows)
add_custom_command(TARGET Sound POST_BUILD
    #COMMAND echo Copying OpenAL32.dll...
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        #$ENV{OPENAL_HOME}/bin/Win64/OpenAL32.dll           #Windows environment variable version
        ${CMAKE_CURRENT_SOURCE_DIR}/openal/bin/OpenAL32.dll #Using the version that is included with the project
        $<TARGET_FILE_DIR:Sound>
)
