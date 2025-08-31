file(GLOB_RECURSE DREAM_ENGINE_SOURCES
    buffers/*.cpp
    buffers/*.h
    input/*cpp
    input/*h
    scene/*.cpp
    scene/*.h
    utils/*.h
    window/*.cpp
    window/*.h
    application.cpp
    application.h
)

# Grouping source files
source_group("buffers" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/buffer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/index_buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/index_buffer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/vertex_array.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/vertex_array.h
)

source_group("input" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/input/input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/input/input.h
    ${CMAKE_CURRENT_SOURCE_DIR}/input/key_codes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/input/mouse_codes.h
)

source_group("scene" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/camera.h

    ${CMAKE_CURRENT_SOURCE_DIR}/scene/group.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/group.h

    ${CMAKE_CURRENT_SOURCE_DIR}/scene/label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/label.h

    ${CMAKE_CURRENT_SOURCE_DIR}/scene/layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/layer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/scene/renderer2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/renderer2D.h

    ${CMAKE_CURRENT_SOURCE_DIR}/scene/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/shader.h

    ${CMAKE_CURRENT_SOURCE_DIR}/scene/texture2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/texture2D.h
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/texture_label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/texture_label.h

    ${CMAKE_CURRENT_SOURCE_DIR}/scene/font_maneger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/font_maneger.h

    ${CMAKE_CURRENT_SOURCE_DIR}/scene/scene_object.h
)

source_group("utils" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/file_utils.h
)

source_group("window" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/window/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window/window.h
)

add_library(DreamEngine ${DREAM_ENGINE_SOURCES})
add_library(DreamEngine::DreamEngine ALIAS DreamEngine)

target_include_directories(DreamEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/log
        ${CMAKE_CURRENT_SOURCE_DIR}/scene
        ${CMAKE_CURRENT_SOURCE_DIR}/events
        ${CMAKE_CURRENT_SOURCE_DIR}/input
        ${CMAKE_CURRENT_SOURCE_DIR}/window
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog.git
    GIT_TAG         v1.15.3
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm.git
    GIT_TAG         1.0.1
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    glad
    GIT_REPOSITORY  https://github.com/Dav1dde/glad.git
    TAG             v2.0.8
)
FetchContent_MakeAvailable(glad)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY  https://github.com/glfw/glfw.git
    GIT_TAG         3.3.10
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    stb_image
    URL             https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
    DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_MakeAvailable(stb_image)

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
    GIT_TAG        VER-2-13-3
    GIT_SHALLOW    FALSE
    GIT_PROGRESS   TRUE
)

set(FT_DISABLE_ZLIB ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BZIP2 ON CACHE BOOL "" FORCE)
set(FT_DISABLE_PNG ON CACHE BOOL "" FORCE)
set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(freetype)

if (TARGET freetype AND NOT TARGET freetype::freetype)
    add_library(freetype::freetype ALIAS freetype)
endif()

# Define an interface target for stb_image
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${stb_image_SOURCE_DIR})

target_link_libraries(DreamEngine PUBLIC spdlog::spdlog glm::glm glad glfw stb_image freetype)
