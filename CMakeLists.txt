cmake_minimum_required(VERSION 3.1)
project(PriMod)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_library(PriMod SHARED dll_main.cpp
        modloader_main.cpp
        api.h "modloader.h")

add_subdirectory(external/minhook)

target_link_libraries(PriMod PRIVATE minhook)

add_subdirectory(external/SFML)

add_subdirectory(external/zlib)

add_subdirectory(external/zlib/contrib/minizip)

add_executable(PriModLoader modloader_main.cpp "modloader.h")


target_link_libraries(PriModLoader PRIVATE SFML::Graphics)
target_link_libraries(PriMod PRIVATE SFML::Graphics)
target_link_libraries(PriModLoader PRIVATE MINIZIP::minizipstatic)
target_link_libraries(PriMod PRIVATE MINIZIP::minizipstatic)

