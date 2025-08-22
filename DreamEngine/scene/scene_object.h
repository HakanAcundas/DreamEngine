#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "renderer2D.h"


namespace dream { namespace graphics {

	class SceneObject
	{
	private:
		bool m_visible = false;

		glm::vec3 m_position;
		glm::vec2 m_size;
		glm::vec4 m_color;

		std::vector<glm::vec2> m_texture_coordinate;
		Texture2D *m_texture;
		Texture2D::SubTexture2D *m_sub_texture;
	public:
		SceneObject()
		{
			m_texture_coordinate.push_back(glm::vec2(0, 0));
			m_texture_coordinate.push_back(glm::vec2(0, 1));
			m_texture_coordinate.push_back(glm::vec2(1, 1));
			m_texture_coordinate.push_back(glm::vec2(1, 0));
		}

		SceneObject(glm::vec3 position, glm::vec2 size, glm::vec4 color)
			: m_position(position), m_size(size), m_color(color) 
		{ 
			m_texture_coordinate.push_back(glm::vec2(0, 0));
			m_texture_coordinate.push_back(glm::vec2(0, 1));
			m_texture_coordinate.push_back(glm::vec2(1, 1));
			m_texture_coordinate.push_back(glm::vec2(1, 0));
		}

		SceneObject(glm::vec3 position, glm::vec2 size, Texture2D *texture)
			: m_position(position), m_size(size), m_color(glm::vec4(0, 0, 0, 0))
		{
			m_texture = texture;
			m_texture_coordinate.push_back(glm::vec2(0, 0));
			m_texture_coordinate.push_back(glm::vec2(0, 1));
			m_texture_coordinate.push_back(glm::vec2(1, 1));
			m_texture_coordinate.push_back(glm::vec2(1, 0));
		}

		SceneObject(glm::vec3 position, glm::vec2 size, Texture2D::SubTexture2D *sub_texture)
			: m_position(position), m_size(size), m_color(glm::vec4(0, 0, 0, 0))
		{
			m_texture = sub_texture->get_texture();
			m_sub_texture = sub_texture;
			m_texture_coordinate.push_back(glm::vec2(0, 0));
			m_texture_coordinate.push_back(glm::vec2(0, 1));
			m_texture_coordinate.push_back(glm::vec2(1, 1));
			m_texture_coordinate.push_back(glm::vec2(1, 0));
		}

		~SceneObject() { }
		virtual void draw() = 0;

		inline const bool is_visible() { return m_visible; }
		inline const void set_visibility(bool visibility) { m_visible = visibility; }

		inline const glm::vec3& get_position() const { return m_position; }
		inline const void set_position(const glm::vec3& new_pos) { m_position = new_pos; }
		inline const void set_position(const float x, const float y, const float z) { m_position = glm::vec3(x, y, z); }

		inline const glm::vec2& get_size() const { return m_size; }
		inline const glm::vec4& get_color() const { return m_color; }
		inline const std::vector<glm::vec2>& get_uv() const { return m_texture_coordinate; }
		inline const Texture2D* get_texture() const { return m_texture; }
		inline const Texture2D::SubTexture2D* get_sub_texture_2d() const { return m_sub_texture; }
	};
}}
