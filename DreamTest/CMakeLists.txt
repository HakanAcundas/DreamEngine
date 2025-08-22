file(GLOB_RECURSE DREAM_TEST_SOURCES
    game/*.cpp
    game/*.h
    game/entities/*.h
    game/main.cpp
    shaders/*.shader
)

add_executable(DreamTest ${DREAM_TEST_SOURCES})

target_link_libraries(DreamTest DreamEngine::DreamEngine)

