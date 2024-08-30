cmake_minimum_required(VERSION 3.15)

option(WGUI_BUILD_EXAMPLES "Build wgui examples" ON)

project(wgui VERSION 0.1 DESCRIPTION "A Library for Native UI Development Using Win32 API")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

file(GLOB SOURCE_FILES
    src/*.cpp
)

add_library(wgui ${SOURCE_FILES})

target_include_directories(wgui PUBLIC include)
target_include_directories(wgui PRIVATE include/wgui include/wgui/utils)

if(WGUI_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()