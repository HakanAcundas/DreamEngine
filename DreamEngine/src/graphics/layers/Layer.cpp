#include "Layer.h"

namespace dream { namespace graphics {

	Layer::Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projectionMatrix)
		:m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
	{
		m_Shader->Enable();
		m_Shader->SetUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->Disable();
	}

	Layer::Layer(Renderer2D* renderer, Shader* shader, Camera camera)
		:m_Renderer(renderer), m_Shader(shader), m_Camera(camera)
	{
		m_Shader->Enable();
		shader->SetUniformMat4("pr_matrix", camera.GetProjectionMatrix());
		shader->SetUniformMat4("ml_matrix", glm::translate(camera.GetViewMatrix(), camera.GetPosition()));
		shader->SetUniform2f("light_pos", glm::vec2(0.0f, 0.0f));
		GLint texIDs[] =
		{
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9
		};
		m_Shader->SetUniform1iv("textures", texIDs, 10);
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

		m_Shader->SetUniformMat4("pr_matrix", m_Camera.GetProjectionMatrix());
		m_Shader->SetUniformMat4("ml_matrix", glm::translate(m_Camera.GetViewMatrix(), m_Camera.GetPosition()));
		for (Renderable* renderable : m_Renderables)
		{
			m_Renderer->Render(renderable);

		}
		m_Renderer->End();
		m_Renderer->Flush();
	}
}}
