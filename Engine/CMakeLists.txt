cmake_minimum_required (VERSION 3.8)

set(GAME_ENGINE_NAME "Engine")

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL3/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL3_image/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Box2D/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/OpenAL/include
)

# Récupérer tous les fichiers cpp
file(GLOB_RECURSE ENGINE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${GAME_ENGINE_NAME}
    ${ENGINE_SOURCES}
)
# Link libraries to project
set(LIBS
    "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL3/lib/x64/SDL3.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL3_image/lib/x64/SDL3_image.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Box2D/lib/box2d.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/OpenAL/lib/Win64/OpenAL32.lib"
)
target_include_directories(${GAME_ENGINE_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${GAME_ENGINE_NAME} ${LIBS})

target_compile_definitions(${GAME_ENGINE_NAME} PRIVATE TEXTURE_PATH=\"${PROJECT_SOURCE_DIR}/Ressources/\")
target_compile_features(${GAME_ENGINE_NAME} PUBLIC cxx_std_23)