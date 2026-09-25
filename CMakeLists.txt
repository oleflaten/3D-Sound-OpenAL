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

target_include_directories(Sound PRIVATE include)

if(APPLE)
    # Explicitly force Homebrew's openal-soft headers and dynamic library
    target_include_directories(Sound PRIVATE /opt/homebrew/opt/openal-soft/include)
    target_link_libraries(Sound PRIVATE /opt/homebrew/opt/openal-soft/lib/libopenal.dylib)
elseif(MSVC)
    target_include_directories(Sound PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/openal/include
    )
    target_link_libraries(Sound PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/openal/lib/OpenAL32.lib
    )

    add_custom_command(TARGET Sound POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/openal/bin/OpenAL32.dll
            $<TARGET_FILE_DIR:Sound>
    )
else()
    find_package(OpenAL REQUIRED)
    target_include_directories(Sound PRIVATE ${OPENAL_INCLUDE_DIR})
    target_link_libraries(Sound PRIVATE ${OPENAL_LIBRARY})
endif()