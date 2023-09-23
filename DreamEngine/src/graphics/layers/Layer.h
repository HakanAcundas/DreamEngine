#pragma once
#include "../renderer/Renderer2D.h"
#include "../Shader.h"
#include "Group.h"

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
			void AddRenderable(Renderable* renderable);
			void RemoveRenderable(Renderable* renderable);
			virtual void Render();
		};
}}
