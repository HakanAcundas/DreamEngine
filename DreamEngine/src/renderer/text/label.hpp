#pragma once

#include <ec/entity.hpp>
#include <string>
#include <glm/glm.hpp>

namespace dream { namespace graphics {
	// TODO: Make label as entity.
	class Label
	{
	private:
		std::string m_text;
	public:
		Label(std::string text, float x, float y, glm::vec4 color);
		~Label();
	};
}}
