cmake_minimum_required (VERSION 3.16)
project(GameProject LANGUAGES CXX)

add_subdirectory(Engine)
add_subdirectory(MyGame)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")