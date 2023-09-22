#include "Group.h"

namespace dream { namespace graphics {

	Group::Group(const glm::mat4& transform)
		: m_TransformationMatrix(transform)
	{
	}

	void Group::Add(Renderable* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	// TODO Transformation Matrix for models
	void Group::Submit(Renderer2D* renderer)
	{
		//renderer->Push(m_TransformationMatrix);
		for (const Renderable* renderable : m_Renderables)
		{
			renderable->Submit(renderer);
		}
		//renderer->Pop();
	}
}}
