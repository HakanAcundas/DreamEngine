#include "Layer.h"

namespace dream { namespace graphics {

	Layer::Layer(const std::string& name = "Dream Layer")
		: m_LayerName(name)
	{

	}

	void Layer::AddRenderable(Entity* entity)
	{
		m_Entities.emplace_back(entity);
	}

	void Layer::RemoveRenderable(Entity* entity)
	{
		auto it = std::find_if(m_Entities.begin(), m_Entities.end(),
			[entity](const std::shared_ptr<Entity>& ptr) {
				return ptr.get() == entity;
			});
		if (it != m_Entities.end())
			m_Entities.erase(it);
	}
}}
