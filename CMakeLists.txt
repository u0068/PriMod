cmake_minimum_required(VERSION 3.0)
project(PriMod)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_library(PriMod SHARED plasmid_api/dll_main.cpp
        plasmid_api/include/api.h)

add_subdirectory(plasmid_api/include/external/minhook)

target_link_libraries(PriMod PRIVATE minhook)

add_executable(PriModLoader pilus_modloader/modloader_main.cpp)