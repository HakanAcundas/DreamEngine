#pragma once
#include "scene_object.h"
#include "renderer2D.h"

namespace dream { namespace graphics {

	class Group : public SceneObject
	{
	private:
		std::vector<SceneObject*> m_scene_objects;
		glm::mat4 m_transformation_mat;

	public:
		Group(const glm::mat4 &transform);
		void add_renderable(SceneObject *object);
		void remove_renderable(SceneObject *object);
	};
}}
