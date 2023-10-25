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
}}
