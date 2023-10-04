#pragma once
#include "../renderer/Renderer2D.h"
#include "../Shader.h"

namespace dream { namespace graphics {

		class Layer
		{
		protected:
			Renderer2D* m_Renderer;
			std::vector<Renderable*> m_Renderables;
			Shader* m_Shader;
			glm::mat4 m_ProjectionMatrix;
			Camera m_Camera;
		protected:
			Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projectionMatrix);
			Layer(Renderer2D* renderer, Shader* shader, Camera camera);

		public:
			virtual ~Layer();
			void AddRenderable(Renderable* renderable);
			void RemoveRenderable(Renderable* renderable);
			virtual void Render();
			void SetCamera(Camera& camera) { m_Camera = camera; }
		};
}}
