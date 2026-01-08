file(GLOB_RECURSE DREAM_TEST_SOURCES
    game/*.cpp
    game/*.hpp
    game/entities/*.hpp
    shaders/*.shader
)

add_executable(DreamTest ${DREAM_TEST_SOURCES})

target_link_libraries(DreamTest DreamEngine::DreamEngine)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})