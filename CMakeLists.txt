cmake_minimum_required(VERSION 3.12)

# Set the project name
project(DreamEngine
    VERSION 0.1.0
    DESCRIPTION "Simple 2D game engine."
    LANGUAGES CXX
)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DREAMENGINE_BUILD_TEST "Build test application." ON)

# Add subdirectories
add_subdirectory(DreamEngine)
if (DREAMENGINE_BUILD_TEST)
    add_subdirectory(DreamTest)
endif()