#pragma once

#include "../Renderable.h"
#include "../Shader.h"

namespace dream { namespace graphics {

		class Layer
		{
		protected:
			Renderer2D* m_Renderer;
			std::vector<Renderable*> m_Renderables;
			Shader* m_Shader;
			glm::mat4 m_ProjectionMatrix;

		protected:
			Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projectionMatrix);

		public:
			virtual ~Layer();
			void Add(Renderable* renderable);
			virtual void Render();
		};
}}
