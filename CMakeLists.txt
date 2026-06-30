cmake_minimum_required(VERSION 3.0)
project(PriMod)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_library(PriMod SHARED dll_main.cpp
        modloader_main.cpp
        api.h)

add_subdirectory(external/minhook)

target_link_libraries(PriMod PRIVATE minhook)

add_executable(PriModLoader modloader_main.cpp)