#include <scene/layer.hpp>
#include <algorithm>

namespace dream { namespace graphics {

	Layer::Layer(const std::string &name = "Dream Layer")
		: m_layer_name(name) { }

	void Layer::add_entity_object(Entity entity)
	{
		m_entities.emplace_back(entity);
	}

	void Layer::remove_entity_object(Entity entity)
	{
		auto it = std::find(m_entities.begin(), m_entities.end(), entity);
		if (it != m_entities.end())
			m_entities.erase(it);
	}
}}
