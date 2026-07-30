#include "layer.hpp"

namespace dream { namespace graphics {

	Layer::Layer(const std::string &name = "Dream Layer")
		: m_layer_name(name) { }

	void Layer::add_entity_object(std::shared_ptr<Entity> entity)
	{
		m_entities.emplace_back(entity);
	}

	void Layer::remove_entity_object(std::shared_ptr<Entity> entity)
	{
		auto it = std::find_if(m_entities.begin(), m_entities.end(),
			[e](const std::shared_ptr<Entity> ptr) {
				return ptr == e;
			});
		if (it != m_entities.end())
			m_entities.erase(it);
	}
}}
