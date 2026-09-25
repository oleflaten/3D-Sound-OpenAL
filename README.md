# 3D-Sound-OpenAL
Small project that sets up OpenAL on Mac<sup>1</sup> and Windows, with a simple wav-reader class.

The project uses CMake, just plain C / C++, and OpenAL.

The project includes a release compiled version of https://github.com/kcat/openal-soft, but should be compatible with the prebuilt https://www.openal.org version as well.

openal-soft is compiled with MSVC from Visual Studio 2019.

1 - the cmake-file is configured on Mac for openal-soft version you get from "brew install openal-soft".
OpenAL used to be included on Mac, but is broken on newer MacOS versions.
