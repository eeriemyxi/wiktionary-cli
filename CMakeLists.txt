cmake_minimum_required(VERSION 3.14)
include(FetchContent)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(wiktionary-cli
    VERSION 1.0 
    DESCRIPTION "Command-line interface for Wiktionary" 
    LANGUAGES CXX)

file(GLOB_RECURSE SOURCES 
    src/proto/*.h
    src/impl/*.cpp
    src/*.cpp
)

add_executable(wiktionary-cli ${SOURCES})

target_compile_features(wiktionary-cli PRIVATE cxx_std_20)

FetchContent_Declare(lexbor
    GIT_REPOSITORY https://github.com/lexbor/lexbor.git
    GIT_TAG v2.3.0
)

FetchContent_Declare(httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.14.1
)

FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.1.1
)

FetchContent_Declare(loguru
    # For some reason their latest tag release is
    # Outdated. So I have to trust their master 
    # branch. It is like this in their CMake example 
    # as well. 
    GIT_REPOSITORY https://github.com/emilk/loguru.git
    GIT_TAG master
)

FetchContent_Declare(CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.3.2
)

FetchContent_MakeAvailable(lexbor httplib fmt loguru CLI11)

target_link_libraries(wiktionary-cli PRIVATE lexbor httplib::httplib fmt loguru::loguru CLI11)
