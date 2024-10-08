#include "texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace dream { namespace graphics {

	Texture2D::Texture2D(std::string path)
		: m_path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		if (data)
		{
			m_width = width;
			m_height = height;

			GLenum internal_format = 0, data_format = 0;
			if (channels == 4)
			{
				internal_format = GL_RGBA8;
				data_format = GL_RGBA;
			}
			else if (channels == 3)
			{
				internal_format = GL_RGB8;
				data_format = GL_RGB;
			}

			glCreateTextures(GL_TEXTURE_2D, 1, &m_tid);
			glTextureStorage2D(m_tid, 1, internal_format, m_width, m_height);

			glTextureParameteri(m_tid, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_tid, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_tid, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_tid, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_tid, 0, 0, 0, m_width, m_height, data_format, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_tid);
	}

	void Texture2D::bind() const
	{
		glBindTextureUnit(GL_TEXTURE_2D, m_tid);

	}

	void Texture2D::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}}