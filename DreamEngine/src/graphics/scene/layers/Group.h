#pragma once
#include "../Renderable.h"
#include "../Renderer2D.h"

namespace dream { namespace graphics {

	class Group : public Renderable
	{
	private:
		std::vector<Renderable*> m_Renderables;
		glm::mat4 m_TransformationMatrix;

	public:
		Group(const glm::mat4& transform);
		void AddRenderable(Renderable* renderable);
		void RemoveRenderable(Renderable* renderable);
	};
}}
