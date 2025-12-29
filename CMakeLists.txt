# CMakeList.txt : projet CMake pour GameEngine, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(GAME_ENGINE_NAME "Engine")
set(GAME_NAME "MyGame")

project (${GAME_NAME})

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/${GAME_ENGINE_NAME}/include
    ${PROJECT_SOURCE_DIR}/${GAME_NAME}/include
    ${PROJECT_SOURCE_DIR}/${GAME_ENGINE_NAME}/Dependencies/SDL3/include
    ${PROJECT_SOURCE_DIR}/${GAME_ENGINE_NAME}/Dependencies/SDL3_image/include
    ${PROJECT_SOURCE_DIR}/${GAME_ENGINE_NAME}/Dependencies/Box2D/include
    ${PROJECT_SOURCE_DIR}/${GAME_ENGINE_NAME}/Dependencies/OpenAL/include
)
include_directories(${INCLUDE_DIRS})

# Récupérer tous les fichiers cpp
file(GLOB_RECURSE ENGINE_SOURCES "${PROJECT_SOURCE_DIR}/${GAME_ENGINE_NAME}/src/*.cpp")
file(GLOB_RECURSE GAME_SOURCES "${PROJECT_SOURCE_DIR}/${GAME_NAME}/src/*.cpp")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (${PROJECT_NAME} ${GAME_SOURCES} ${ENGINE_SOURCES})

# Link libraries to project
set(LIBS
    "${PROJECT_SOURCE_DIR}/${GAME_ENGINE_NAME}/Dependencies/SDL3/lib/x64/SDL3.lib"
    "${PROJECT_SOURCE_DIR}/${GAME_ENGINE_NAME}/Dependencies/SDL3_image/lib/x64/SDL3_image.lib"
    "${PROJECT_SOURCE_DIR}/${GAME_ENGINE_NAME}/Dependencies/Box2D/lib/box2d.lib"
    "${PROJECT_SOURCE_DIR}/${GAME_ENGINE_NAME}/Dependencies/OpenAL/lib/Win64/OpenAL32.lib"
)
target_link_libraries(${PROJECT_NAME} ${LIBS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/Engine/Dependencies/SDL3/lib/x64/SDL3.dll"
    "${PROJECT_SOURCE_DIR}/Engine/Dependencies/SDL3_image/lib/x64/SDL3_image.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
# TODO: Ajoutez des tests et installez des cibles si nécessaire.
