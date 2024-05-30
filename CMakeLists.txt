cmake_minimum_required(VERSION 3.10)

# Project name
project(DreamEngine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add thirdparty libraries
set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/../thirdparty)

# Include directories
include_directories(
    ${THIRDPARTY_DIR}/glew/include
    ${THIRDPARTY_DIR}/glfw/include
    ${THIRDPARTY_DIR}/glm
    ${THIRDPARTY_DIR}/stb_image
    ${THIRDPARTY_DIR}/freetype/include
    ${CMAKE_SOURCE_DIR}/DreamEngine/core
    ${CMAKE_SOURCE_DIR}/DreamEngine/events
    ${CMAKE_SOURCE_DIR}/DreamEngine/scene
    ${CMAKE_SOURCE_DIR}/DreamEngine/utils
    ${CMAKE_SOURCE_DIR}/DreamEngine/window
)

# Add DreamEngine library
file(GLOB_RECURSE DREAMENGINE_SOURCES
    DreamEngine/core/buffers/*.cpp
    DreamEngine/core/buffers/*.h
    DreamEngine/events/*.h
    DreamEngine/scene/*.cpp
    DreamEngine/scene/*.h
    DreamEngine/utils/*.h
    DreamEngine/window/*.cpp
    DreamEngine/window/*.h
    DreamEngine/Application.cpp
    DreamEngine/Application.h
)

add_library(DreamEngine STATIC ${DREAMENGINE_SOURCES})

# Link thirdparty libraries to DreamEngine
target_link_libraries(DreamEngine
    ${THIRDPARTY_DIR}/glew/lib/x64/glew32s.lib
    ${THIRDPARTY_DIR}/glfw/lib-vc2022/glfw3.lib
    opengl32.lib
)

# Add DreamTest executable
file(GLOB_RECURSE DREAMTEST_SOURCES
    DreamTest/game/*.cpp
    DreamTest/game/*.h
)

add_executable(DreamTest ${DREAMTEST_SOURCES})

# Link DreamEngine library to DreamTest
target_link_libraries(DreamTest DreamEngine)
