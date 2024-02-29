#include "Label.h"

namespace dream { namespace graphics {

	Label::Label(std::string text, float x, float y, glm::vec4 color)
		: Renderable(), m_Text(text)
	{

	}

	Label::~Label()
	{

	}
}}