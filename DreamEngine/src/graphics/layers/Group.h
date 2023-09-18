#pragma once

#include "../Renderable.h"

namespace dream { namespace graphics {

	class Group : public Renderable
	{
	private:
		std::vector<Renderable*> m_Renderables;
		glm::mat4 m_TransformationMatrix;
	public:
		Group(const glm::mat4& transform);
		void Add(Renderable* renderable);
		//void Submit(Renderer2D* renderer) const override;
		//~Group();
	};
}}
