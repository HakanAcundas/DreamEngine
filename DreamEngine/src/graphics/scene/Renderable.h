#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Texture2D.h"

namespace dream { namespace graphics {

	class Renderable
	{
	private:
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		glm::vec4 m_Color;

		std::vector<glm::vec2> m_TextureCoordinate;
		Texture2D* m_Texture;
	public:
		Renderable()
		{
			m_TextureCoordinate.push_back(glm::vec2(0, 0));
			m_TextureCoordinate.push_back(glm::vec2(0, 1));
			m_TextureCoordinate.push_back(glm::vec2(1, 1));
			m_TextureCoordinate.push_back(glm::vec2(1, 0));
		}

		Renderable(glm::vec3 position, glm::vec2 size, glm::vec4 color)
			: m_Position(position), m_Size(size), m_Color(color) 
		{ 
			m_TextureCoordinate.push_back(glm::vec2(0, 0));
			m_TextureCoordinate.push_back(glm::vec2(0, 1));
			m_TextureCoordinate.push_back(glm::vec2(1, 1));
			m_TextureCoordinate.push_back(glm::vec2(1, 0));
		}

		Renderable(glm::vec3 position, glm::vec2 size, Texture2D* texture)
			: m_Position(position), m_Size(size), m_Color(glm::vec4(1, 0, 1, 0))
		{
			m_Texture = texture;
			m_TextureCoordinate.push_back(glm::vec2(0, 0));
			m_TextureCoordinate.push_back(glm::vec2(0, 1));
			m_TextureCoordinate.push_back(glm::vec2(1, 1));
			m_TextureCoordinate.push_back(glm::vec2(1, 0));
		}

		~Renderable() 
		{ 

		}

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec2& GetSize() const { return m_Size; }
		inline const glm::vec4& GetColor() const { return m_Color; }
		inline const std::vector<glm::vec2>& GetUV() const { return m_TextureCoordinate; }
		inline const Texture2D* GetTexture() const { return m_Texture; }
	};
}}
