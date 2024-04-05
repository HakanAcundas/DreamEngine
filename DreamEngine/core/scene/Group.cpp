#include "Group.h"

namespace dream { namespace graphics {

	Group::Group(const glm::mat4& transform)
		: m_TransformationMatrix(transform)
	{
	}

	void Group::AddRenderable(Renderable* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Group::RemoveRenderable(Renderable* renderable)
	{
		m_Renderables.erase(std::remove(m_Renderables.begin(), m_Renderables.end(), renderable), m_Renderables.end());
	}
}}
