#include "texture2d.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture2D::Texture2D(const std::string& path)
{
	stbi_set_flip_vertically_on_load(true);  // OpenGL UV origin is bottom-left

	int w, h, channels;
	uint8_t* data = stbi_load(path.c_str(), &w, &h, &channels, 4); // force RGBA
	if (!data) return;

	m_width = w;
	m_height = h;
	create(data, GL_RGBA);
	stbi_image_free(data);
}

Texture2D::~Texture2D()
{
	if (m_tid)
		glDeleteTextures(1, &m_tid);
}

void Texture2D::create(const uint8_t* pixels, GLenum format)
{
	glGenTextures(1, &m_tid);
	glBindTexture(GL_TEXTURE_2D, m_tid);

	// Pixel-art games: no blurring when scaling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Don't repeat texture at edges
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels);
}

void Texture2D::upload_sub_region(int x, int y, int w, int h, const uint8_t* pixels) const
{
	glBindTexture(GL_TEXTURE_2D, m_tid);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

void Texture2D::bind(unsigned int slot = 0)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_tid);
}

void Texture2D::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
