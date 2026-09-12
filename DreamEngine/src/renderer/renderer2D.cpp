#include <renderer/renderer2D.hpp>
#include "utils/file_utils.hpp"

namespace dream { namespace graphics {
  Renderer2D::Renderer2D()
  {
    m_vertex_staging.resize(MAX_VERTICES);

    m_vao = VertexArray();
    m_vao.bind();
    m_vbo = VertexBuffer(MAX_VERTICES * sizeof(Vertex));
    m_vbo.bind();
    m_ibo = IndexBuffer(MAX_QUADS);
    m_ibo.bind();
    m_vao.set_sprite_layout();
    m_vao.unbind();

    m_shader = Shader("shaders/vertex.shader", "shaders/fragment.shader");
    m_shader.bind();

    int samplers[MAX_TEXTURES];
    for (int i = 0; i < (int)MAX_TEXTURES; ++i)
      samplers[i] = i;

    m_shader.set_int_array("u_textures", samplers, MAX_TEXTURES);
    m_shader.unbind();

    // Slot 0 is always a white pixel.
    uint8_t white[4] = { 255, 255, 255, 255 };
    m_white_texture = std::make_shared<Texture2D>(1, 1, white);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  // Camera / projection
  // Call once per frame before submitting sprites.
  // view_projection = projection_matrix * view_matrix
  void Renderer2D::begin_scene(const SceneData& scene)
  {
    m_view_projection = scene.view_projection;
    m_light_pos = scene.light_pos;
    begin_batch();
  }

  void Renderer2D::end_scene()
  {
    flush();
  }

  void Renderer2D::draw_sprite(glm::vec2& position, glm::vec2& size, std::shared_ptr<Texture2D> texture, float rotation, const glm::vec4& color, const glm::vec4& uv_rect)
  {
    if (m_quad_count >= MAX_QUADS)
      flush_and_begin();

    float tex_idx = get_or_bind_texture(texture);
    push_quad(position, size, rotation, color, uv_rect, tex_idx);
  }

  void Renderer2D::draw_rect(glm::vec2& position, glm::vec2& size, glm::vec4& color, float rotation)
  {
    draw_sprite(position, size, m_white_texture, rotation, color, { 0,0,1,1 });
  }

  void Renderer2D::draw_rect(glm::vec2&& position, glm::vec2&& size, glm::vec4&& color, float rotation)
  {
    draw_sprite(position, size, m_white_texture, rotation, color, { 0,0,1,1 });
  }

  void Renderer2D::begin_batch()
  {
    m_quad_count = 0;
    m_vertex_write_ptr = m_vertex_staging.data();
    m_texture_slot_idx = 1;   // slot 0 = white texture, always bound
  }

  void Renderer2D::flush()
  {
    if (m_quad_count == 0)
      return;

    // Upload only the vertices we actually wrote this batch
    uint32_t vertex_count = m_quad_count * 4;
    std::size_t data_size = vertex_count * sizeof(Vertex);

    m_vao.bind();
    m_vbo.bind();
    m_vbo.upload_sub(m_vertex_staging.data(), data_size);

    // Bind all textures used this batch, slot 0 always white
    m_white_texture->bind(0);
    for (unsigned int i = 1; i < m_texture_slot_idx; i++)
      m_texture_slots[i]->bind(i);

    // One draw call for the entire batch
    m_shader.bind();
    m_shader.set_mat4("u_view_projection", m_view_projection);

    glDrawElements(GL_TRIANGLES, m_quad_count * 6, GL_UNSIGNED_INT, nullptr);

    ++m_stats.draw_calls;
    m_stats.quad_count += m_quad_count;
  }

  void Renderer2D::flush_and_begin()
  {
    flush();
    begin_batch();
  }

  // Write 4 vertices into the CPU staging buffer
  //
  // The quad corners in local space (before rotation):
  //   3 ---- 2
  //   |      |    center = (0,0), half-extents = size/2
  //   0 ---- 1
  void Renderer2D::push_quad(glm::vec2& center,glm::vec2& size, float rotation, const glm::vec4& color, const glm::vec4& uv, float tex_idx)
  {
    glm::vec2 half = size * 0.5f;

    // Local corners
    glm::vec2 corners[4] = {
        { -half.x, -half.y },   // 0 bottom-left
        {  half.x, -half.y },   // 1 bottom-right
        {  half.x,  half.y },   // 2 top-right
        { -half.x,  half.y },   // 3 top-left
    };

    // Apply rotation if needed
    if (rotation != 0.0f)
    {
      float c = std::cos(rotation);
      float s = std::sin(rotation);
      for (auto& p : corners)
        p = { p.x * c - p.y * s, p.x * s + p.y * c };
    }

    // UVs per corner
    glm::vec2 uvs[4] = {
        { uv.x, uv.y },   // 0 bottom-left
        { uv.z, uv.y },   // 1 bottom-right
        { uv.z, uv.w },   // 2 top-right
        { uv.x, uv.w },   // 3 top-left
    };

    for (int i = 0; i < 4; ++i)
    {
      m_vertex_write_ptr->position = center + corners[i];
      m_vertex_write_ptr->uv = uvs[i];
      m_vertex_write_ptr->tex_index = tex_idx;
      m_vertex_write_ptr->color = color;
      ++m_vertex_write_ptr;
    }

    ++m_quad_count;
  }

  // Check if this texture is already in our slot list.
  // If yes, return its slot index.
  // If no, assign it the next free slot, return that index.
  // If all 32 slots full, flush first, then assign slot 1.
  float Renderer2D::get_or_bind_texture(std::shared_ptr<Texture2D> tex)
  {
    // if texture is null, use white (slot 0)
    if (!tex)
      return 0.0f;

    for (unsigned int i = 1; i < m_texture_slot_idx; ++i)
    {
      if (m_texture_slots[i]->get_tid() == tex->get_tid())
        return static_cast<float>(i);
    }

    if (m_texture_slot_idx >= MAX_TEXTURES)
      flush_and_begin();

    m_texture_slots[m_texture_slot_idx] = tex;
    return static_cast<float>(m_texture_slot_idx++);
  }
}}
