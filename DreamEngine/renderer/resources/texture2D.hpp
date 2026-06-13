#pragma once

#include <cstdint>
#include <string>
#include <glad/glad.h>

class Texture2D
{
public:
	Texture2D() = default;
	Texture2D(const std::string& path);
	~Texture2D();

	void bind(unsigned int slot = 0);
	void unbind();
	void upload_sub_region(int x, int y, int w, int h, const uint8_t* pixels) const;

	unsigned int	get_width()  const { return m_width; }
	unsigned int	get_height() const { return m_height; }
	unsigned int	get_tid()     const { return m_tid; }
	bool					is_valid()  const { return m_tid != 0; }

private:
	void create(const uint8_t* pixels, GLenum format);

	unsigned int	m_tid = 0;
	uint32_t			m_width = 0;
	uint32_t			m_height = 0;
};