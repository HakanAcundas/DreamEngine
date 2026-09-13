#pragma once

#include <cstdint>
#include <string>
#include <glad/glad.h>

class Texture_Manager
{
public:
	Texture_Manager() = default;
	Texture_Manager(const std::string& path);
	Texture_Manager(unsigned int width, unsigned int height, uint8_t* rgba_pixels);
	~Texture_Manager();

	void create_texture(const uint8_t* pixels, GLenum format);
	void create_sub_texture(int x, int y, int w, int h, const uint8_t* pixels) const;
	void bind(unsigned int slot = 0);
	void unbind();
};