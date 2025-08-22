#include "layer.h"

namespace dream { namespace graphics {

	Layer::Layer(const std::string &name = "Dream Layer")
		: m_layer_name(name)
	{

	}

	void Layer::add_renderable(Entity *entity)
	{
		m_entities.emplace_back(entity);
	}

	void Layer::remove_renderable(Entity *entity)
	{
		auto it = std::find_if(m_entities.begin(), m_entities.end(),
			[entity](const std::shared_ptr<Entity>& ptr) {
				return ptr.get() == entity;
			});
		if (it != m_entities.end())
			m_entities.erase(it);
	}
}}
