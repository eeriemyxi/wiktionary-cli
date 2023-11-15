cmake_minimum_required(VERSION 3.14)
include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(wiktionary-cli 
    VERSION 1.0 
    DESCRIPTION "Command-line interface for Wiktionary" 
    LANGUAGES CXX)

file(GLOB SOURCES 
    src/proto/*.h
    src/impl/*.cpp
    src/*.cpp
)

add_executable(wiktionary-cli ${SOURCES})

target_compile_features(wiktionary-cli PRIVATE cxx_std_20)

FetchContent_Declare(lexbor
    GIT_REPOSITORY https://github.com/lexbor/lexbor.git
)
FetchContent_MakeAvailable(lexbor)

FetchContent_Declare(httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
)
FetchContent_MakeAvailable(httplib)

target_link_libraries(wiktionary-cli PRIVATE lexbor)
target_link_libraries(wiktionary-cli PRIVATE httplib::httplib)
