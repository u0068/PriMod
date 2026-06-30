cmake_minimum_required(VERSION 3.28)
project(PriMod)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_library(PriMod SHARED dllmain.cpp primordialis.h
        main.cpp
        main.h)

add_subdirectory(external/minhook)
add_subdirectory(external/SFML)

target_link_libraries(PriMod PRIVATE minhook)


add_executable(PriModLoader main.cpp main.h)

target_link_libraries(PriModLoader PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

project(Basic_DLL_Injector)

add_executable(inject main.cpp)