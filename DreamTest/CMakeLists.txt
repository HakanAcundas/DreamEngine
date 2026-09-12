file(GLOB_RECURSE DREAM_TEST_SOURCES
    demo_game/*.cpp
    demo_game/*.hpp
    game/layers/*.hpp
    game/layers/*.cpp
    game/entities/*.hpp
)

add_executable(DreamTest ${DREAM_TEST_SOURCES})

set_target_properties(DreamTest PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:DreamTest>")

target_link_libraries(DreamTest DreamEngine::DreamEngine)

# Copy shaders next to the actual .exe, resolved at build time (works correctly
# with multi-config generators like Visual Studio, unlike file(COPY) at configure time)
add_custom_command(TARGET DreamTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/DreamEngine/resources/shaders
        $<TARGET_FILE_DIR:DreamTest>/shaders
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})