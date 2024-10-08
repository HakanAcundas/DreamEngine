# =====================================
# Gather Source Files for DreamTest
# =====================================
file(GLOB_RECURSE DREAM_TEST_SOURCES
    game/*.cpp
    game/*.h
    game/main.cpp
    shaders/*.shader
)

# =====================================
# Add DreamTest Executable
# =====================================
add_executable(DreamTest ${DREAM_TEST_SOURCES})

# =====================================
# Platform-Specific Configuration
# =====================================
if (WIN32)
    message(STATUS "Configuring for Windows")

    # Link libraries for Windows
    target_link_libraries(DreamTest 
        DreamEngine
        ${THIRD_PARTY_DIR}/glew/lib/x64/glew32s.lib
        ${THIRD_PARTY_DIR}/glfw/lib-vc2022/glfw3.lib
        opengl32.lib
    )

elseif (UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux (Ubuntu)")

    # Set output directory for DreamTest executable
    set_target_properties(DreamTest PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

    # Link libraries for Linux
    target_link_libraries(DreamTest 
        DreamEngine
        glfw
        ${OPENGL_LIBRARIES}
        ${FREETYPE_LIBRARIES}
    )

else ()
    message(FATAL_ERROR "Unsupported platform")
endif()

# =====================================
# Include Directories (Common for All Platforms)
# =====================================
target_include_directories(DreamTest PRIVATE
    ${THIRD_PARTY_DIR}/glad/include
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

# =====================================
# Organize Source Files into Groups
# =====================================
source_group("game" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/game/game_layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/game_layer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/game/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/test_level.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game/test_level.h
)

source_group("shaders" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertex.shader
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragment.shader
)

# =====================================
# Set Default Build Type and Debug Flags
# =====================================
# Set build type to Debug if not already specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add debugging symbols for GCC/Clang in Debug mode
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
