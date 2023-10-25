//#include "MapLayer.h"
//
//namespace dream { namespace graphics {
//
//	MapLayer::MapLayer(Shader* shader)
//	{
//		m_Shader->Enable();
//		m_Shader->SetUniformMat4("pr_matrix", m_ProjectionMatrix);
//		m_Shader->Disable();
//	}
//
//	MapLayer::MapLayer(Shader* shader, Camera camera)
//		:m_Shader(shader), m_Camera(camera)
//	{
//		m_Shader->Enable();
//		shader->SetUniformMat4("pr_matrix", camera.GetProjectionMatrix());
//		shader->SetUniformMat4("ml_matrix", glm::translate(camera.GetViewMatrix(), camera.GetPosition()));
//		shader->SetUniform2f("light_pos", glm::vec2(0.0f, 0.0f));
//		GLint texIDs[] =
//		{
//			0, 1, 2, 3, 4, 5, 6, 7, 8, 9
//		};
//		m_Shader->SetUniform1iv("textures", texIDs, 10);
//		m_Shader->Disable();
//	}
//
//	MapMapLayer::~MapMapLayer()
//	{
//		delete m_Shader;
//		for (int i = 0; i < m_Renderables.size(); i++)
//		{
//			delete m_Renderables[i];
//		}
//	}
//
//	void MapMapLayer::AddRenderable(Renderable* renderable)
//	{
//		m_Renderables.push_back(renderable);
//	}
//
//	void MapMapLayer::RemoveRenderable(Renderable* renderable)
//	{
//		m_Renderables.erase(std::remove(m_Renderables.begin(), m_Renderables.end(), renderable), m_Renderables.end());
//	}
//
//	// Her MapMapLayerin rendereri olmamali. Tek bir static renderer olsun
//	void MapLayer::Render()
//	{
//		m_Shader->Enable();
//
//		m_Shader->SetUniformMat4("pr_matrix", m_Camera.GetProjectionMatrix());
//		m_Shader->SetUniformMat4("ml_matrix", glm::translate(m_Camera.GetViewMatrix(), m_Camera.GetPosition()));
//		for (Renderable* renderable : m_Renderables)
//		{
//			m_Renderer->Render(renderable);
//
//		}
//	}
//}