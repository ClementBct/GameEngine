cmake_minimum_required (VERSION 3.20)
project(Engine LANGUAGES CXX)

set(GAME_ENGINE_NAME "Engine")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

#dependencies
# find_package(SDL3 REQUIRED)
# find_package(SDL3_image REQUIRED)
# find_package(box2d REQUIRED)
# find_package(OpenAL REQUIRED)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)

# Récupérer tous les fichiers cpp
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(${GAME_ENGINE_NAME})
target_sources(${GAME_ENGINE_NAME} PRIVATE ${ENGINE_SOURCES})

target_include_directories(${GAME_ENGINE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${GAME_ENGINE_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    box2d::box2d
    OpenAL::OpenAL
)

target_compile_definitions(${GAME_ENGINE_NAME} PRIVATE TEXTURE_PATH=\"${PROJECT_SOURCE_DIR}/Ressources/\")

target_compile_features(${GAME_ENGINE_NAME}  PRIVATE 
    CXX_STANDARD_23
)
if(MSVC)
    target_compile_options(${GAME_ENGINE_NAME} PRIVATE /W4 /permissive-)

else()
    target_compile_options(${GAME_ENGINE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()