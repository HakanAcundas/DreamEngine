#include "group.h"

namespace dream { namespace graphics {

	Group::Group(const glm::mat4 &transform)
		: m_transformation_mat(transform)
	{
	}

	void Group::add_renderable(Entity *entity)
	{
		m_entities.push_back(entity);
	}

	void Group::remove_renderable(Entity *entity)
	{
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
	}
}}
