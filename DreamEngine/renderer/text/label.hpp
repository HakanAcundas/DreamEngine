#pragma once
#include <string>
#include <glm/glm.hpp>

namespace dream { namespace graphics {

	class Label
	{
	private:
		std::string m_text;
	public:
		Label(std::string text, float x, float y, glm::vec4 color);
		~Label();
	};

}}
