file(GLOB_RECURSE DREAM_ENGINE_SOURCES
  # Implementation and private headers.
  src/*.cpp
  src/*.hpp
  # Public headers: listed only so they show up in the IDE's file tree.
  include/dream/*.hpp
  renderer/resources/shaders/*.shader
)

# Mirrors the on-disk layout
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${DREAM_ENGINE_SOURCES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/renderer/resources/shaders
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_library(DreamEngine ${DREAM_ENGINE_SOURCES})
add_library(DreamEngine::DreamEngine ALIAS DreamEngine)

target_include_directories(DreamEngine
  # The engine's public API. Consumers get this, and it is the ONLY thing they get,
  # so every engine include is spelled <dream/...> and has exactly one valid path.
  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
  # Implementation detail. Not propagated to consumers, so DreamTest has no include
  # path that can reach anything in src/ -- enforced by the compiler, not convention.
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
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
