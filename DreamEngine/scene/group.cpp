#include "group.h"

namespace dream { namespace graphics {

	Group::Group(const glm::mat4 &transform)
		: m_transformation_mat(transform)
	{
	}

	void Group::add_renderable(SceneObject *object)
	{
		m_scene_objects.push_back(object);
	}

	void Group::remove_renderable(SceneObject *object)
	{
		m_scene_objects.erase(std::remove(m_scene_objects.begin(), m_scene_objects.end(), object), m_scene_objects.end());
	}
}}
