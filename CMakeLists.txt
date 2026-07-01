cmake_minimum_required(VERSION 3.1)
project(PriMod)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_library(PriMod SHARED plasmid_api/dll_main.cpp
        plasmid_api/include/api.h)

add_subdirectory(plasmid_api/include/external/minhook)


add_subdirectory(pilus_modloader/external/SFML)

add_subdirectory(pilus_modloader/external/zlib)

add_subdirectory(pilus_modloader/external/zlib/contrib/minizip)

add_executable(PriModLoader pilus_modloader/modloader_main.cpp pilus_modloader/modloader.h)

target_link_libraries(PriModLoader PRIVATE SFML::Graphics)
target_link_libraries(PriModLoader PRIVATE MINIZIP::minizipstatic)
