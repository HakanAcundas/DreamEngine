#pragma once
#include <cstddef>
#include <map>
#include "../buffers/vertex_array.h"
#include "../scene/shader.h"
#include "../scene/camera.h"
#include "../scene/texture2D.h"
#include "../scene/texture_label.h"
#include "../scene/font_manager.h"

namespace dream { namespace graphics {

#define RENDERER_MAX_RENDERABLE	20000
#define RENDERER_VERTEX_SIZE	sizeof(QuadVertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4 
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_RENDERABLE
#define RENDERER_INDICES_SIZE	RENDERER_MAX_RENDERABLE * 6

	struct QuadVertexData
	{
		glm::vec3 position;
		glm::vec2 texture_coord;
		float texture_id;
		glm::vec4 color;
	};

	struct RendererData
	{
		Buffer* buffer;
		VertexArray* vertex_array;
		IndexBuffer* index_buffer;
		std::vector<unsigned int> texture_slots;
		FT_Library ft;

		QuadVertexData* quad_buffer = nullptr;
		uint32_t index_count;
		glm::vec4 vertex_positions[4];
		glm::vec2 texture_coords[4];

		struct CameraData
		{
			glm::mat4 view_projection;
		};
		CameraData camera_buffer;
	};

	class Renderer2D
	{
	private:
		static Renderer2D *singleton;
		Renderer2D();
		float submit_texture(const unsigned int &texture_id);
	public:
		static Renderer2D* get_instance() { return singleton; }

		Renderer2D(const Renderer2D *obj) = delete;
		void init();
		void begin();
		void end();
		// void load_font(const std::string &font_path);

		void draw_quad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
		void draw_quad(const glm::vec2 &position, const glm::vec2 &size, const Texture2D *texture );
		void draw_quad(const glm::vec2 &position, const glm::vec2 &size, const Texture2D::SubTexture2D *sub_texture);

		void draw_label(const std::string& text, const glm::vec2& position, const std::string& font_path, const glm::vec4& color);
		
		void flush();
		//void shut_down();

	};
}}
