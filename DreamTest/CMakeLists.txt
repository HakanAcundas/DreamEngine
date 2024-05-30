# Project name
project(DreamTest)

# Add DreamTest executable
file(GLOB_RECURSE DREAM_TEST_SOURCES
    game/*.cpp
    game/*.h
)

add_executable(DreamTest ${DREAM_TEST_SOURCES})

# Specify output directories for DreamTest
set_target_properties(DreamTest PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamTest/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamTest/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamTest/bin
)

# Include directories for DreamTest
target_include_directories(DreamTest PRIVATE
    ${CMAKE_SOURCE_DIR}/DreamEngine/core
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/buffers
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/events
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/scene
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/utils
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/window
    ${THIRD_PARTY_DIR}/glew/include
    ${THIRD_PARTY_DIR}/glfw/include
    ${THIRD_PARTY_DIR}/glm
    ${THIRD_PARTY_DIR}/stb_image
    ${THIRD_PARTY_DIR}/freetype/include
)

# Link DreamEngine library to DreamTest
target_link_libraries(DreamTest DreamEngine)
