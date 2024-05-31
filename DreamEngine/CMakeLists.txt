# Include directories
include_directories(
    ${THIRD_PARTY_DIR}/glew/include
    ${THIRD_PARTY_DIR}/glfw/include
    ${THIRD_PARTY_DIR}/glm
    ${THIRD_PARTY_DIR}/stb_image
    ${THIRD_PARTY_DIR}/freetype/include
)

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

# Add preprocessor definitions globally
add_compile_definitions(GLEW_STATIC _CRT_SECURE_NO_WARNINGS)

# # Specify output directories for DreamEngine
# set_target_properties(DreamEngine PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamEngine/lib
#     LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamEngine/lib
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/DreamEngine/bin
# )

# Group source files into folders
source_group("core/buffers" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/Buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/Buffer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/IndexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/IndexBuffer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/VertexArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/buffers/VertexArray.h
)

source_group("core/events" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/events/Event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/core/events/KeyEvent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/core/events/MouseEvent.h
)

source_group("core/input" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/input/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/input/Input.h
    ${CMAKE_CURRENT_SOURCE_DIR}/core/input/KeyCodes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/core/input/MouseCodes.h
)

source_group("core/scene" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Camera.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Group.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Group.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Label.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Layer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Renderable.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Renderer2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Renderer2D.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Shader.h

    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Texture2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/scene/Texture2D.h
)

source_group("core/utils" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/utils/FileUtils.h
)

source_group("core/window" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/window/Window.h
)

source_group("core" FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/Application.h
)


# Link thirdparty libraries to DreamEngine
target_link_libraries(DreamEngine
    ${THIRD_PARTY_DIR}/glew/lib/x64/glew32s.lib
    ${THIRD_PARTY_DIR}/glfw/lib-vc2022/glfw3.lib
    opengl32.lib
    ${THIRD_PARTY_DIR}/freetype/lib/freetype.lib
)
