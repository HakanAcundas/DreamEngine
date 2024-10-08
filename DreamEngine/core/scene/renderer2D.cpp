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
		FT_Library ft;

		if (FT_Init_FreeType(&ft))
		{
			std::cout << "Failed to compile FreeType: " << std::endl << &ft << std::endl;
		}

		r_data.texture_coords[0] = { 0.0f, 0.0f };
		r_data.texture_coords[1] = { 1.0f, 0.0f };
		r_data.texture_coords[2] = { 1.0f, 1.0f };
		r_data.texture_coords[3] = { 0.0f, 1.0f };

		r_data.r_vertex_positions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		r_data.r_vertex_positions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		r_data.r_vertex_positions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		r_data.r_vertex_positions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		r_data.r_index_count = 0;
		r_data.vertex_array = new VertexArray();
		r_data.buffer = new Buffer(RENDERER_BUFFER_SIZE);

		// The order of the buffer-elements must be the same as the vertex-shader layout order
		r_data.buffer->add_buffer_element("shader_Position", ShaderDataType::Float, 3);
		r_data.buffer->add_buffer_element("shader_TexCoord", ShaderDataType::Float, 2);
		r_data.buffer->add_buffer_element("shader_TextureID", ShaderDataType::Float, 1);
		r_data.buffer->add_buffer_element("shader_Color", ShaderDataType::Float, 4);
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
		r_data.r_data = (RenderableData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		r_data.buffer->unbind();
	}

	float Renderer2D::submit_texture(const Texture2D *texture)
	{
		const unsigned int tid = texture->get_tid();
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

	// TODO convert this function into DrawQuad (its is already converted but make a base 
	// function to apply different variations of DrawQuad. Example DrawRotatedQuad etc...
	void Renderer2D::draw_renderable(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (int i = 0; i < 4; i++)
		{
			r_data.r_data->position = transform * r_data.r_vertex_positions[i];
			r_data.r_data->color = color;
			r_data.r_data->texture_coord = r_data.texture_coords[i];
			r_data.r_data->texture_id = 0;
			r_data.r_data++;
		}

		r_data.r_index_count += 6;
	}

	void Renderer2D::draw_renderable(const glm::vec2 &position, const glm::vec2 &size, const Texture2D *texture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		float ts = 0;
		if (texture != NULL)
			ts = submit_texture(texture);

		for (int i = 0; i < 4; i++)
		{
			r_data.r_data->position = transform * r_data.r_vertex_positions[i];
			r_data.r_data->color = glm::vec4(0, 0, 0, 0);
			r_data.r_data->texture_coord = r_data.texture_coords[i];
			r_data.r_data->texture_id = ts;
			r_data.r_data++;
		}
		
		r_data.r_index_count += 6;
	}

	void Renderer2D::draw_renderable(const glm::vec2 &position, const glm::vec2 &size, const Texture2D::SubTexture2D *subTexture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		float ts = 0;
		if (subTexture->get_texture() != NULL)
			ts = submit_texture(subTexture->get_texture());

		for (int i = 0; i < 4; i++)
		{
			r_data.r_data->position = transform * r_data.r_vertex_positions[i];
			r_data.r_data->color = glm::vec4(0, 0, 0, 0);
			r_data.r_data->texture_coord = subTexture->get_tex_coords()[i];
			r_data.r_data->texture_id = ts;
			r_data.r_data++;
		}

		r_data.r_index_count += 6;
	}

	void Renderer2D::draw_label(const std::string &text, float x, float y, const glm::vec4 &color)
	{
		
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
		glDrawElements(GL_TRIANGLES, r_data.r_index_count, GL_UNSIGNED_INT, NULL);
		r_data.index_buffer->unbind();
		r_data.vertex_array->unbind();
		
		r_data.r_index_count = 0;
	}
}}
