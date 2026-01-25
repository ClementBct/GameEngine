set(GAME_NAME "MyGame")

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Récupérer tous les fichiers cpp
file(GLOB_RECURSE GAME_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (${GAME_NAME} ${GAME_SOURCES})
target_include_directories(${GAME_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${GAME_NAME} PRIVATE Engine)

add_custom_command(TARGET ${GAME_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/Engine/Dependencies/SDL3/lib/x64/SDL3.dll"
    "${PROJECT_SOURCE_DIR}/Engine/Dependencies/SDL3_image/lib/x64/SDL3_image.dll"
    $<TARGET_FILE_DIR:${GAME_NAME}>
)
# TODO: Ajoutez des tests et installez des cibles si nécessaire.