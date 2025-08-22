#pragma once
#include <string>
#include <glad/glad.h> 
#include <glm/glm.hpp>

namespace dream { namespace graphics {

	class Texture2D
	{
	public:
		typedef struct {
			unsigned int	c_texture_id;	// texture id storing character
			glm::ivec2		c_size;			// size of char
			glm::ivec2		c_bearing;		// distance from origin to top left of char
			unsigned int	c_advance;		// distance from origin to next origin (1/64th pixels)
		} Character;

		class SubTexture2D
		{
		public:
			SubTexture2D(Texture2D *texture, const glm::vec2 &min, const glm::vec2 &max)
				: m_texture(texture)
			{
				m_TexCoords[0] = { min.x, min.y };
				m_TexCoords[1] = { max.x, min.y };
				m_TexCoords[2] = { max.x, max.y };
				m_TexCoords[3] = { min.x, max.y };
			}

			Texture2D *get_texture() const { return m_texture; }
			const glm::vec2 *get_tex_coords() const { return m_TexCoords; }
		private:
			Texture2D *m_texture;
			glm::vec2 m_TexCoords[4];
		};

	private:
		std::string m_path;
		unsigned int m_width, m_height;
		unsigned int  m_tid;
	public:
		Texture2D(std::string path);
		Texture2D(unsigned int texture_id) : m_tid(texture_id) {}
		~Texture2D();

		void set_data(void *data, unsigned int size);
		void bind() const;
		void unbind() const;

		static SubTexture2D* create_sub_texture_2d(Texture2D *texture, const glm::vec2 coords, const glm::vec2 sprite_size)
		{
			glm::vec2 min = { (coords.x * sprite_size.x) / texture->get_width(), (coords.y * sprite_size.y) / texture->get_height()};
			glm::vec2 max = { ((coords.x + 1) * sprite_size.x) / texture->get_width(), ((coords.y + 1) * sprite_size.y) / texture->get_height()};
			return new SubTexture2D(texture, min, max);
		}

		const std::string get_path() const { return m_path; }
		unsigned int get_height() const { return m_height; }
		unsigned int get_width() const { return m_width; }
		unsigned int get_tid() const { return m_tid; }
	};
}}