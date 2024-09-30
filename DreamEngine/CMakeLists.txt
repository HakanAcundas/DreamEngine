# Include directories
include_directories(
    ${THIRD_PARTY_DIR}/glad/include
    ${THIRD_PARTY_DIR}/glfw/include
    ${THIRD_PARTY_DIR}/glm
    ${THIRD_PARTY_DIR}/stb_image
    ${THIRD_PARTY_DIR}/freetype/include
)

# Find OpenGL and Freetype
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

# Add GLAD as a library
add_library(glad ${THIRD_PARTY_DIR}/glad/src/glad.c)

# Add DreamEngine library
file(GLOB_RECURSE DREAM_ENGINE_SOURCES
    core/buffers/*.cpp
    core/buffers/*.h
    core/events/*.h
    core/input/*cpp
    core/input/*h
    core/scene/*.cpp
    core/scene/*.h
    core/utils/*.h
    core/window/*.cpp
    core/window/*.h
    core/Application.cpp
    core/Application.h
)

add_library(DreamEngine STATIC ${DREAM_ENGINE_SOURCES})
#add_compile_definitions(GLEW_STATIC _CRT_SECURE_NO_WARNINGS)

# Grouping source files
source_group("core/buffers" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/buffer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/index_buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/index_buffer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/vertex_array.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/vertex_array.h
)

source_group("core/events" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/events/event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/core/events/key_event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/core/events/mouse_event.h
)

source_group("core/input" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/input/input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/input/input.h
    ${CMAKE_CURRENT_SOURCE_DIR}/core/input/key_codes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/core/input/mouse_codes.h
)

source_group("core/scene" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/camera.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/group.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/group.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/label.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/layer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/entity.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/renderer2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/renderer2D.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/shader.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/texture2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/texture2D.h
)

source_group("core/utils" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/utils/file_utils.h
)

source_group("core/window" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window/window.h
)

source_group("core" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/application.h
)

# Link thirdparty libraries to DreamEngine
if (WIN32)
    message(STATUS "Configuring for Windows")
    target_link_libraries(DreamEngine
        ${THIRD_PARTY_DIR}/glew/lib/x64/glew32s.lib
        ${THIRD_PARTY_DIR}/glfw/lib-vc2022/glfw3.lib
        opengl32.lib
        ${THIRD_PARTY_DIR}/freetype/lib/freetype.lib
    )
    add_library(DreamEngine STATIC ${DREAM_ENGINE_SOURCES})
elseif (UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux (Ubuntu)")

    # Set output directory for DreamEngine static library
    set_target_properties(DreamEngine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

    # Linux-specific settings
    # Link third-party libraries to DreamEngine
    target_link_libraries(DreamEngine
        glad
        glfw
        ${FREETYPE_LIBRARIES}
        ${OPENGL_LIBRARIES}
    )
    set_target_properties(DreamEngine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
else ()
    message(FATAL_ERROR "Unsupported platform")
endif ()

# Ensure Freetype include directories are added
target_include_directories(DreamEngine PRIVATE ${FREETYPE_INCLUDE_DIRS})
