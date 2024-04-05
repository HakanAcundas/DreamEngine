#include "Layer.h"

namespace dream { namespace graphics {

	Layer::Layer(const std::string& name = "Dream Layer")
		: m_LayerName(name)
	{

	}

	void Layer::AddRenderable(Renderable* renderable)
	{
		m_Renderables.emplace_back(renderable);
	}

	void Layer::RemoveRenderable(Renderable* renderable)
	{
		auto it = std::find_if(m_Renderables.begin(), m_Renderables.end(),
			[renderable](const std::shared_ptr<Renderable>& ptr) {
				return ptr.get() == renderable;
			});
		if (it != m_Renderables.end())
			m_Renderables.erase(it);
	}
}}
