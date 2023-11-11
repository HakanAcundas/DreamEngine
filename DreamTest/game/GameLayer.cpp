#include "GameLayer.h"

namespace dream { namespace graphics {

	GameLayer::GameLayer(Shader* shader)
		: Layer(m_Renderer, "GameLayer"), m_Shader(shader)
	{
		m_Shader->Enable();
		m_Shader->SetUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->Disable();
	}

	GameLayer::GameLayer(Shader* shader, Camera* camera)
		: Layer(m_Renderer, "GameLayer"), m_Shader(shader), m_Camera(camera)
	{
		m_Shader->Enable();
		shader->SetUniformMat4("pr_matrix", camera->GetProjectionMatrix());
		shader->SetUniformMat4("ml_matrix", glm::translate(camera->GetViewMatrix(), camera->GetPosition()));
		shader->SetUniform2f("light_pos", glm::vec2(0.0f, 0.0f));
		GLint texIDs[] =
		{
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9
		};
		m_Shader->SetUniform1iv("textures", texIDs, 10);
		m_Shader->Disable();
	}

	GameLayer::~GameLayer()
	{
		delete m_Shader;
		for (int i = 0; i < m_Renderables.size(); i++)
		{
			delete m_Renderables[i];
		}
	}

	void GameLayer::OnUpdate()
	{
		m_Shader->SetUniformMat4("pr_matrix", m_Camera->GetProjectionMatrix());
		m_Shader->SetUniformMat4("ml_matrix", glm::translate(m_Camera->GetViewMatrix(), m_Camera->GetPosition()));
	}

	void GameLayer::Render()
	{
		m_Shader->Enable();
		OnUpdate();
		Renderer2D::GetSingleton()->Begin();
		for(Renderable* renderable : m_Renderables)
		{
			Renderer2D::GetSingleton()->DrawRenderable(renderable->GetPosition(), renderable->GetSize(), renderable->GetTID(), renderable->GetColor());
		}
		Renderer2D::GetSingleton()->End();
		Renderer2D::GetSingleton()->Flush();
	}
}}
