#pragma once
#include "scene_object.h"

namespace dream { namespace graphics {

	class Label : public SceneObject
	{
	private:
		std::string m_text;
	public:
		Label(std::string text, float x, float y, glm::vec4 color);
		~Label();
	};

}}
