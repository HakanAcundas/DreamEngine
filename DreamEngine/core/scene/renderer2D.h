#pragma once
#include <cstddef>
#include <map>
#include <ft2build.h>
#include "../buffers/vertex_array.h"
#include "../scene/shader.h"
#include "../scene/camera.h"
#include "../scene/entity.h"
#include FT_FREETYPE_H

namespace dream { namespace graphics {

#define RENDERER_MAX_RENDERABLE	20000
#define RENDERER_VERTEX_SIZE	sizeof(RenderableData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4 
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_RENDERABLE
#define RENDERER_INDICES_SIZE	RENDERER_MAX_RENDERABLE * 6

	typedef struct {
		unsigned int	c_texture_id;	// texture id storing character
		glm::ivec2		c_size;			// size of char
		glm::ivec2		c_bearing;		// distance from origin to top left of char
		unsigned int	c_advance;		// distance from origin to next origin (1/64th pixels)
	} Character;

	struct RenderableData
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
		std::map<char, Character> characters;

		RenderableData* r_data = nullptr;
		uint32_t r_index_count;
		glm::vec4 r_vertex_positions[4];
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
		float submit_texture(const Texture2D *texture);
	public:
		static Renderer2D* get_singleton() { return singleton; }

		Renderer2D(const Renderer2D *obj) = delete;
		void init();
		void begin();
		void end();

		void draw_renderable(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
		void draw_renderable(const glm::vec2 &position, const glm::vec2 &size, const Texture2D *texture );
		void draw_renderable(const glm::vec2 &position, const glm::vec2 &size, const Texture2D::SubTexture2D *subTexture);
		void draw_label(const std::string &text, float x, float y, const glm::vec4 &color);

		void flush();
		//void shut_down();

	};
}}
