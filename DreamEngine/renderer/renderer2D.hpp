#pragma once
#include <cstddef>
#include <memory>
#include <array>
#include <map>
#include "../buffers/vertex_buffer.hpp"
#include "../buffers/index_buffer.hpp"
#include "../buffers/vertex_array.hpp"
#include "resources/shader.hpp"
#include "resources/texture2d.hpp"
#include "text/texture_label.hpp"
#include "text/font_manager.hpp"

using namespace dream::buffer;

namespace dream { namespace graphics {
	// One vertex = one corner of a sprite quad
	// 36 bytes total = stride
	struct Vertex
	{
		glm::vec2 position; //  8 bytes — world position
		glm::vec4 color;    // 16 bytes — tint (1,1,1,1 = no tint)
		glm::vec2 uv;       //  8 bytes — texture coordinate (0..1)
		float tex_index;		//  4 bytes — which of the 32 slots to sample
	};

	// Sprite descriptor
	struct SpriteQuad
	{
		glm::vec2 position;								// center of sprite in world space
		glm::vec2 size;										// width/height in world units
		float rotation = 0.0f;						// radians, clockwise
		glm::vec4 color = { 1,1,1,1 };		// tint, alpha
		glm::vec4 uv_rect = { 0,0,1,1 };	// {u_min, v_min, u_max, v_max} — for sprite sheets
		Texture2D* texture = nullptr;
		int z_layer = 0;									// higher = drawn on top (sort before flush)
	};

	class Renderer2D
	{
	public:
		static constexpr unsigned int MAX_QUADS = 20000;  // max sprites per batch
		static constexpr unsigned int MAX_VERTICES = MAX_QUADS * 4;
		static constexpr unsigned int MAX_INDICES = MAX_QUADS * 6;
		static constexpr unsigned int MAX_TEXTURES = 32;  // OpenGL guarantees >= 32 slots

		Renderer2D();
		void begin_scene(const glm::mat4& view_projection);
		void end_scene();
		void draw_sprite(glm::vec2& position, glm::vec2& size, std::shared_ptr<Texture2D> texture, float rotation = 0.0f, const glm::vec4& color = { 1,1,1,1 }, const glm::vec4& uv_rect = { 0,0,1,1 });
		void draw_rect(glm::vec2& position, glm::vec2& size, glm::vec4& color, float rotation = 0.0f);
		
#pragma region Stats
		// Stats — useful during development
		struct Stats
		{
			uint32_t draw_calls = 0;
			uint32_t quad_count = 0;
		};
		Stats get_stats() const
		{
			return m_stats;
		}
		void  reset_stats()
		{
			m_stats = {};
		}
#pragma endregion

	private:
		void begin_batch();
		void flush();
		void flush_and_begin();
		void push_quad(glm::vec2& center, glm::vec2& size, float rotation, const glm::vec4& color, const glm::vec4& uv, float tex_idx);
		float get_or_bind_texture(std::shared_ptr<Texture2D> tex);

		VertexArray m_vao;
		VertexBuffer m_vbo;
		IndexBuffer m_ibo;
		Shader m_shader;
		Texture2D m_white_texture;

		// CPU staging buffer — we write here, then upload once per flush
		std::vector<Vertex> m_vertex_staging;
		Vertex* m_vertex_write_ptr = nullptr;

		// Texture slot tracking
		std::array<std::shared_ptr<Texture2D>, MAX_TEXTURES> m_texture_slots = {};
		uint32_t m_texture_slot_idx = 1;  // 0 = white, 1..31 = user textures

		uint32_t  m_quad_count = 0;
		glm::mat4 m_view_projection = glm::mat4(1.0f);

		// For debug
		Stats m_stats;
	};
}}
