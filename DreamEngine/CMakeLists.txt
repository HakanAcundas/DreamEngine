file(GLOB_RECURSE DREAM_ENGINE_SOURCES
    buffers/*.hpp
    buffers/*.cpp
    events/*.hpp
    events/*.cpp
    camera/*hpp
    camera/*cpp
    renderer/*hpp
    renderer/*cpp
    renderer/resources/*.hpp
    renderer/resources/*.cpp
    renderer/text/*.hpp
    renderer/text/*.cpp
    ecs/*.hpp
    ecs/*.cpp
    ecs/components/*.hpp
    ecs/systems/*.hpp
    scene/*.hpp
    scene/*.cpp
    utils/*.hpp
    window/*.hpp
    window/*.cpp
    application.hpp
    application.cpp
)

source_group("event" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/events/event.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/events/event_dispatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/events/event_dispatcher.cpp
)

# Grouping source files
source_group("buffers" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/buffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/buffer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/index_buffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/index_buffer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/vertex_array.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/buffers/vertex_array.cpp
)

source_group("ecs" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/signature.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/entity.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/entity_manager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/entity_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/component_array.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/component_manager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/system_manager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/ecs_manager.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/components/transfrom.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/systems
)

source_group("renderer" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/renderer2D.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/renderer2D.cpp
)


source_group("renderer\\resources" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/resources/shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/resources/shader.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/texture2D.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/texture2D.cpp
)

source_group("renderer\\text" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/text/font_manager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/text/font_manager.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/text/label.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/text/label.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/text/texture_label.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/text/texture_label.cpp
)

source_group("camera" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/camera.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/camera.cpp
)

source_group("scene" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/layer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene/layer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/scene/scene_object.hpp
)

source_group("utils" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/file_utils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/metric_utils.hpp
)

source_group("window" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/window/window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window/window.cpp
)

add_library(DreamEngine ${DREAM_ENGINE_SOURCES})
add_library(DreamEngine::DreamEngine ALIAS DreamEngine)

target_include_directories(DreamEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/log
        ${CMAKE_CURRENT_SOURCE_DIR}/events
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/resources
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/text
        ${CMAKE_CURRENT_SOURCE_DIR}/camera
        ${CMAKE_CURRENT_SOURCE_DIR}/scene
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

add_library(glad thirdparty/glad/src/glad.c)
target_include_directories(glad PUBLIC thirdparty/glad/include)

target_link_libraries(DreamEngine PUBLIC spdlog::spdlog glm::glm glfw glad stb_image freetype)
