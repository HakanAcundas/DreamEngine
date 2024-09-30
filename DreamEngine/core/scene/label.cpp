#include "label.h"

namespace dream { namespace graphics {

	Label::Label(std::string text, float x, float y, glm::vec4 color)
		: Entity(), m_Text(text)
	{

	}

	Label::~Label()
	{

	}
}}