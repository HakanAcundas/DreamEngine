#include "Layer.h"

namespace dream { namespace graphics {

		Layer::Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projectionMatrix)
			:m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
		{
			m_Shader->Enable();
			m_Shader->SetUniformMat4("pr_matrix", m_ProjectionMatrix);
			m_Shader->Disable();
		}

		Layer::~Layer()
		{
			delete m_Shader;
			delete m_Renderer;
			for (int i = 0; i < m_Renderables.size(); i++)
			{
				delete m_Renderables[i];
			}
		}

		void Layer::AddRenderable(Renderable* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Layer::RemoveRenderable(Renderable* renderable)
		{
			m_Renderables.erase(std::remove(m_Renderables.begin(), m_Renderables.end(), renderable), m_Renderables.end());
		}

		void Layer::Render()
		{
			m_Shader->Enable();
			m_Renderer->Begin();

			//for (Renderable* renderable : m_Renderables)
			//{
			//	m_Renderer->AddRenderable(renderable);
			//}
			m_Renderer->Render();

			m_Renderer->End();
			m_Renderer->Flush();
		}
}}
