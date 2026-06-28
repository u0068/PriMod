cmake_minimum_required(VERSION 3.30)
project(PriMod)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_library(PriMod SHARED dllmain.cpp primordialis.h
        main.cpp
        main.h)

add_subdirectory(external/minhook)

target_link_libraries(PriMod PRIVATE minhook)

add_executable(PriModLoader main.cpp main.h)