#pragma once

#include <cstdint>
#include <string>
#include <glad/glad.h>

class Texture2D
{
public:
	Texture2D() = default;
	Texture2D(const std::string& path);
	Texture2D(unsigned int width, unsigned int height, uint8_t* rgba_pixels);
	~Texture2D();

	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;
	Texture2D(Texture2D&& other) noexcept;
	Texture2D& operator=(Texture2D&& other) noexcept;

	void bind(unsigned int slot = 0);
	void unbind();
	void upload_sub_region(int x, int y, int w, int h, const uint8_t* pixels) const;

	unsigned int get_width() const { return m_width; }
	unsigned int get_height() const { return m_height; }
	unsigned int get_tid() const { return m_tid; }
	bool is_valid() const { return m_tid != 0; }

private:
	void create(const uint8_t* pixels, GLenum format);

	unsigned int m_tid = 0;
	unsigned int m_width = 0;
	unsigned int m_height = 0;
};