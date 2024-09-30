#include "group.h"

namespace dream { namespace graphics {

	Group::Group(const glm::mat4& transform)
		: m_TransformationMatrix(transform)
	{
	}

	void Group::AddRenderable(Entity* entity)
	{
		m_Entities.push_back(entity);
	}

	void Group::RemoveRenderable(Entity* entity)
	{
		m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), entity), m_Entities.end());
	}
}}
