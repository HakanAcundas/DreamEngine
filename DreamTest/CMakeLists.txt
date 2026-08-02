file(GLOB_RECURSE DREAM_TEST_SOURCES
    demo_game/*.cpp
    demo_game/*.hpp
    game/layers/*.hpp
    game/layers/*.cpp
    game/entities/*.hpp
)

add_executable(DreamTest ${DREAM_TEST_SOURCES})

target_link_libraries(DreamTest DreamEngine::DreamEngine)

# Copy shaders next to the actual .exe, resolved at build time (works correctly
# with multi-config generators like Visual Studio, unlike file(COPY) at configure time)
add_custom_command(TARGET DreamTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/DreamEngine/renderer/resources/shaders
        $<TARGET_FILE_DIR:DreamTest>/shaders
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})