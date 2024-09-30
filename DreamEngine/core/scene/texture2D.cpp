#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace dream { namespace graphics {

	Texture2D::Texture2D(std::string path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		if (data)
		{
			m_Width = width;
			m_Height = height;

			GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			glCreateTextures(GL_TEXTURE_2D, 1, &m_TID);
			glTextureStorage2D(m_TID, 1, internalFormat, m_Width, m_Height);

			glTextureParameteri(m_TID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_TID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_TID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_TID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_TID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_TID);
	}

	void Texture2D::Bind() const
	{
		glBindTextureUnit(GL_TEXTURE_2D, m_TID);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}}