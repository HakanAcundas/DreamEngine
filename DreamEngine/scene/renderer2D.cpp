#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderer2D.h"
#include <iostream>

namespace dream { namespace graphics {

	static RendererData r_data;
	Renderer2D *Renderer2D::singleton = nullptr;

	void Renderer2D::init()
	{
		if (FT_Init_FreeType(&r_data.ft))
		{
			std::cout << "ERROR::FREETYPE: Could not initialize FreeType Library" << std::endl;
			return;
		}

		glEnable(GL_BLEND);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		r_data.texture_coords[0] = { 0.0f, 0.0f };
		r_data.texture_coords[1] = { 1.0f, 0.0f };
		r_data.texture_coords[2] = { 1.0f, 1.0f };
		r_data.texture_coords[3] = { 0.0f, 1.0f };

		r_data.vertex_positions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		r_data.vertex_positions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		r_data.vertex_positions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		r_data.vertex_positions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		r_data.index_count = 0;
		r_data.vertex_array = new VertexArray();
		r_data.buffer = new Buffer(RENDERER_BUFFER_SIZE);

		// The order of the buffer-elements must be the same as the vertex-shader layout order
		r_data.buffer->add_buffer_element("position", ShaderDataType::Float, 3);
		r_data.buffer->add_buffer_element("texcoord", ShaderDataType::Float, 2);
		r_data.buffer->add_buffer_element("texture_id", ShaderDataType::Float, 1);
		r_data.buffer->add_buffer_element("color", ShaderDataType::Float, 4);
		r_data.buffer->calculate_stride();
		
		r_data.vertex_array->add_buffer(r_data.buffer);

		unsigned int *quad_indices = new unsigned int[RENDERER_INDICES_SIZE];
		unsigned int offset = 0;
		for (unsigned int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			quad_indices[i + 0] = offset + 0;
			quad_indices[i + 1] = offset + 1;
			quad_indices[i + 2] = offset + 2;

			quad_indices[i + 3] = offset + 2;
			quad_indices[i + 4] = offset + 3;
			quad_indices[i + 5] = offset + 0;

			offset += 4;
		}

		r_data.index_buffer = new IndexBuffer(quad_indices, RENDERER_INDICES_SIZE);
		r_data.vertex_array->set_index_buffer(r_data.index_buffer);
		r_data.vertex_array->unbind();
	}

	void Renderer2D::begin()
	{
		r_data.buffer->bind();
		r_data.quad_buffer = (QuadVertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		r_data.buffer->unbind();
	}

	float Renderer2D::submit_texture(const unsigned int &tid)
	{
		float ts = 0.0f;
		if (tid > 0)
		{
			bool found = false;
			// Search for texture ID
			for (int i = 0; i < r_data.texture_slots.size(); i++)
			{
				if (r_data.texture_slots[i] == tid)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				// If the texture slots are full
				if (r_data.texture_slots.size() >= 32)
				{
					end();
					flush();
					begin();
				}
				// Else add the new texture ID to a slot
				r_data.texture_slots.push_back(tid);
				ts = (float)(r_data.texture_slots.size());
			}
		}

		return ts;
	}

	void Renderer2D::draw_quad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < 4; i++)
		{
			r_data.quad_buffer->position = transform * r_data.vertex_positions[i];
			r_data.quad_buffer->color = color;
			r_data.quad_buffer->texture_coord = r_data.texture_coords[i];
			r_data.quad_buffer->texture_id = 0;
			r_data.quad_buffer++;
		}

		r_data.index_count += 6;
	}

	void Renderer2D::draw_quad(const glm::vec2 &position, const glm::vec2 &size, const Texture2D *texture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		float ts = 0;
		if (texture != NULL)
			ts = submit_texture(texture->get_tid());

		for (int i = 0; i < 4; i++)
		{
			r_data.quad_buffer->position = transform * r_data.vertex_positions[i];
			r_data.quad_buffer->color = glm::vec4(0, 0, 0, 0);
			r_data.quad_buffer->texture_coord = r_data.texture_coords[i];
			r_data.quad_buffer->texture_id = ts;
			r_data.quad_buffer++;
		}
		
		r_data.index_count += 6;
	}

	void Renderer2D::draw_quad(const glm::vec2 &position, const glm::vec2 &size, const Texture2D::SubTexture2D *sub_texture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		float ts = 0;
		if (sub_texture->get_texture() != NULL)
			ts = submit_texture(sub_texture->get_texture()->get_tid());

		for (int i = 0; i < 4; i++)
		{
			r_data.quad_buffer->position = transform * r_data.vertex_positions[i];
			r_data.quad_buffer->color = glm::vec4(0, 0, 0, 0);
			r_data.quad_buffer->texture_coord = sub_texture->get_tex_coords()[i];
			r_data.quad_buffer->texture_id = ts;
			r_data.quad_buffer++;
		}

		r_data.index_count += 6;
	}

	void Renderer2D::draw_label(const std::string& text, const glm::vec2& position, const std::string& font_path, const glm::vec4& color) {
		TextureLabel* font = FontManager::get_font(font_path);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f)) *
                      glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 1.0f)); // Scale down

		for (const char& c : text) {
			const TextureLabel::Character& ch = font->get_characters().at(c);

			float xpos = ch.c_bearing.x;
			float ypos = ch.c_size.y - ch.c_bearing.y;
			float width = ch.c_size.x;
			float height = ch.c_size.y;

			// Apply transform to each character position
			glm::vec4 top_left = transform * glm::vec4(xpos, ypos, 0.0f, 1.0f);
			glm::vec4 top_right = transform * glm::vec4(xpos + width, ypos, 0.0f, 1.0f);
			glm::vec4 bottom_left = transform * glm::vec4(xpos, ypos + height, 0.0f, 1.0f);
			glm::vec4 bottom_right = transform * glm::vec4(xpos + width, ypos + height, 0.0f, 1.0f);

			float ts = submit_texture(ch.c_texture_id);

			r_data.quad_buffer->position = top_left;
			r_data.quad_buffer->texture_coord = { 0.0f, 1.0f };
			r_data.quad_buffer->texture_id = ts;
			r_data.quad_buffer->color = color;
			r_data.quad_buffer++;

			r_data.quad_buffer->position = bottom_left;
			r_data.quad_buffer->texture_coord = { 0.0f, 0.0f };
			r_data.quad_buffer->texture_id = ts;
			r_data.quad_buffer->color = color;
			r_data.quad_buffer++;

			r_data.quad_buffer->position = bottom_right;
			r_data.quad_buffer->texture_coord = { 1.0f, 0.0f };
			r_data.quad_buffer->texture_id = ts;
			r_data.quad_buffer->color = color;
			r_data.quad_buffer++;

			r_data.quad_buffer->position = top_right;
			r_data.quad_buffer->texture_coord = { 1.0f, 1.0f };
			r_data.quad_buffer->texture_id = ts;
			r_data.quad_buffer->color = color;
			r_data.quad_buffer++;

			r_data.index_count += 6;

			transform = glm::translate(transform, glm::vec3((ch.c_advance >> 6), 0.0f, 0.0f));
		}
	}


	void Renderer2D::flush()
	{
		for (int i = 0; i < r_data.texture_slots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, r_data.texture_slots[i]);
		}
		
		r_data.vertex_array->bind();
		r_data.index_buffer->bind();
		glDrawElements(GL_TRIANGLES, r_data.index_count, GL_UNSIGNED_INT, NULL);
		r_data.index_buffer->unbind();
		r_data.vertex_array->unbind();
		
		r_data.index_count = 0;
	}
}}
