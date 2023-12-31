#include "Layer.h"

namespace dream { namespace graphics {

	Layer::Layer(Renderer2D& renderer, const std::string& name = "Dream Layer")
		: m_Renderer(renderer), m_LayerName(name)
	{

	}

	void Layer::AddRenderable(Renderable* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Layer::RemoveRenderable(Renderable* renderable)
	{
		m_Renderables.erase(std::remove(m_Renderables.begin(), m_Renderables.end(), renderable), m_Renderables.end());
	}

	//void Layer::Render()
	//{
	//	Renderer2D::GetSingleton()->Begin();
	//	m_Shader->Enable();
	//	OnUpdate();
	//	for (Renderable* renderable : m_Renderables)
	//	{
	//		Renderer2D::GetSingleton()->DrawRenderable(renderable->GetPosition(), renderable->GetSize(), renderable->GetTexture(), renderable->GetColor());
	//	}
	//	Renderer2D::GetSingleton()->End();
	//	Renderer2D::GetSingleton()->Flush();
	//}
}}
