#pragma once
#include "entity.h"
#include "renderer2D.h"

namespace dream { namespace graphics {

	class Group : public Entity
	{
	private:
		std::vector<Entity*> m_entities;
		glm::mat4 m_transformation_mat;

	public:
		Group(const glm::mat4 &transform);
		void add_renderable(Entity *entity);
		void remove_renderable(Entity *entity);
	};
}}
