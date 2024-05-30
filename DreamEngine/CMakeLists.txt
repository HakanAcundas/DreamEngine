# Project name
project(DreamEngine)

# Include directories
include_directories(
    ${THIRD_PARTY_DIR}/glew/include
    ${THIRD_PARTY_DIR}/glfw/include
    ${THIRD_PARTY_DIR}/glm
    ${THIRD_PARTY_DIR}/stb_image
    ${THIRD_PARTY_DIR}/freetype/include
    ${CMAKE_SOURCE_DIR}/DreamEngine/core
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/buffers
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/events
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/scene
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/utils
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/window
)

# Add DreamEngine library
file(GLOB_RECURSE DREAM_ENGINE_SOURCES
    core/buffers/*.cpp
    core/buffers/*.h
    core/events/*.h
    core/scene/*.cpp
    core/scene/*.h
    core/utils/*.h
    core/window/*.cpp
    core/window/*.h
    core/Application.cpp
    core/Application.h
)

add_library(DreamEngine STATIC ${DREAM_ENGINE_SOURCES})

# Specify output directories for DreamEngine
set_target_properties(DreamEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamEngine/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamEngine/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamEngine/bin
)

# Link thirdparty libraries to DreamEngine
target_link_libraries(DreamEngine
    ${THIRD_PARTY_DIR}/glew/lib/x64/glew32s.lib
    ${THIRD_PARTY_DIR}/glfw/lib-vc2022/glfw3.lib
    opengl32.lib
)
