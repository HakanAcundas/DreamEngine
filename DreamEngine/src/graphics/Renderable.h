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
		float TexIndex;
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
		~Renderable() { }

		//// Submit is neccesarry?? Investigate since we can diretly submit it via draw function in Renderer
		//void Submit(Renderer2D* renderer) const
		//{
		//	renderer->Submit(this);
		//}

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec2& GetSize() const { return m_Size; }
		inline const glm::vec4& GetColor() const { return m_Color; }
		inline const std::vector<glm::vec2>& GetUV() const { return m_TextureCoordinate; }
		inline const unsigned int GetTID() const { return m_Texture == nullptr ? 0 : m_Texture->GetRendererID(); }
	};
}}
