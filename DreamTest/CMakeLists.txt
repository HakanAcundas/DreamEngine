# Add DreamTest executable
file(GLOB_RECURSE DREAM_TEST_SOURCES
    game/*.cpp
    game/*.h
    shaders/*.shader
)

add_executable(DreamTest ${DREAM_TEST_SOURCES})

# Add preprocessor definitions globally
add_compile_definitions(GLEW_STATIC _CRT_SECURE_NO_WARNINGS)

# # Specify output directories for DreamTest
# set_target_properties(DreamTest PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamTest/lib
#     LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamTest/lib
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamTest/bin
# )
message(STATUS "Include directories: ${THIRD_PARTY_DIR}/glew/include")
# Include directories for DreamTest
target_include_directories(DreamTest PRIVATE
    ${THIRD_PARTY_DIR}/glew/include
    ${THIRD_PARTY_DIR}/glfw/include
    ${THIRD_PARTY_DIR}/glm
    ${THIRD_PARTY_DIR}/stb_image
    ${THIRD_PARTY_DIR}/freetype/include
    ${CMAKE_SOURCE_DIR}/DreamEngine/core
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/buffers
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/events
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/input
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/scene
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/utils
    ${CMAKE_SOURCE_DIR}/DreamEngine/core/window
)

source_group("game" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/game/GameLayer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/GameLayer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/game/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/TestLevel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/TestLevel.h
)

source_group("shaders" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertex.shader
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragment.shader
)

# Link DreamEngine library to DreamTest
target_link_libraries(DreamTest 
    DreamEngine
    ${THIRD_PARTY_DIR}/glew/lib/x64/glew32s.lib
    ${THIRD_PARTY_DIR}/glfw/lib-vc2022/glfw3.lib
    opengl32.lib
)
