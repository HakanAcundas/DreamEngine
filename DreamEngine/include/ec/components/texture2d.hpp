#pragma once

#include <cstdint>
#include <glm/glm.hpp>

using TexHandle = std::uint32_t;

struct Texture2D
{
  TexHandle handle;
  glm::vec4 uv_rect = { 0, 0, 1, 1 };
};