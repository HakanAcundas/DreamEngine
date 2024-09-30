#pragma once
#include "entity.h"

namespace dream { namespace graphics {

	class Label : public Entity
	{
	private:
		std::string m_Text;
	public:
		Label(std::string text, float x, float y, glm::vec4 color);
		~Label();
	};

}}
