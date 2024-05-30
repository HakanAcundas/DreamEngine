cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DreamEngine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SUPPRESS_REGENERATION true)

# Add thirdparty libraries
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/thirdparty)

# Add subdirectories
add_subdirectory(DreamEngine)
add_subdirectory(DreamTest)
