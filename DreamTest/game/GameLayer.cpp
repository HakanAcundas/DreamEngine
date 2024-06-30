#include "GameLayer.h"
#include "MouseEvent.h"

using namespace dream;
using namespace graphics;

GameLayer::GameLayer(Shader* shader)
	: Layer("GameLayer"), m_Shader(shader)
{
	m_Shader->Enable();
	m_Shader->SetUniformMat4("pr_matrix", m_ProjectionMatrix);
	m_Shader->Disable();
}

GameLayer::GameLayer(Shader* shader, Camera* camera)
	: Layer("GameLayer"), m_Shader(shader), m_Camera(camera)
{
	m_Shader->Enable();
	m_Shader->SetUniformMat4("pr_matrix", camera->GetProjectionMatrix());
	m_Shader->SetUniformMat4("ml_matrix", glm::translate(camera->GetViewMatrix(), camera->GetPosition()));
	m_Shader->SetUniform2f("light_pos", glm::vec2(0.0f, 0.0f));
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
	for (int i = 0; i < m_Entities.size(); i++)
	{
		delete &m_Entities[i];
	}
}

void GameLayer::OnUpdate()
{
	Renderer2D::GetSingleton()->Begin();
	m_Shader->SetUniformMat4("pr_matrix", m_Camera->GetProjectionMatrix());
	m_Shader->SetUniformMat4("ml_matrix", glm::translate(m_Camera->GetViewMatrix(), m_Camera->GetPosition()));
	m_Shader->SetUniform2f("light_pos", m_LightPos);
	m_Camera->OnUpdate();
	SetCamera(m_Camera);
	m_Shader->Enable();
	for(Entity* entity : m_Level.GetWalls())
	{
		Renderer2D::GetSingleton()->DrawRenderable(entity->GetPosition(), entity->GetSize(), entity->GetTexture());
	}

	Renderer2D::GetSingleton()->DrawRenderable(m_Level.GetPlayer()->GetPosition(),
		m_Level.GetPlayer()->GetSize(), m_Level.GetPlayer()->GetTexture());

	for (Entity* entity : m_Level.GetEnemies())
	{
		Renderer2D::GetSingleton()->DrawRenderable(entity->GetPosition(), entity->GetSize(), entity->GetSubTexture2D());
	}

	Renderer2D::GetSingleton()->End();
	Renderer2D::GetSingleton()->Flush();
}

void GameLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseMovedEvent>(std::bind(&GameLayer::OnMouseMoved, this, std::placeholders::_1));
	dispatcher.Dispatch<KeyPressedEvent>(std::bind(&GameLayer::OnKeyPressed, this, std::placeholders::_1));
}

bool GameLayer::OnMouseMoved(MouseMovedEvent& e)
{
	if (!e.handled)
	{
		m_LightPos.x = (float)((double)e.GetX() * 16.0f/ 1280.0f);
		m_LightPos.y = (float)(9.0f - (double)e.GetY() * 9.0f / 720.0f);
	}
	return false;
}

bool GameLayer::OnKeyPressed(KeyPressedEvent& e)
{
	glm::vec3 playerPos = m_Level.GetPlayer()->GetPosition();
	switch (e.GetKeyCode())
	{
	case 87:
		m_Level.GetPlayer()->SetPosition(playerPos.x + 0.02, playerPos.y, playerPos.z);
	}

	return false;
}
