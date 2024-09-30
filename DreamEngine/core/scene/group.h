#pragma once
#include "entity.h"
#include "renderer2D.h"

namespace dream { namespace graphics {

	class Group : public Entity
	{
	private:
		std::vector<Entity*> m_Entities;
		glm::mat4 m_TransformationMatrix;

	public:
		Group(const glm::mat4& transform);
		void AddRenderable(Entity* entity);
		void RemoveRenderable(Entity* entity);
	};
}}
