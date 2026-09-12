#pragma once
#include <memory>
#include <string>
#include <vector>
#include <ec/entity.hpp>

namespace dream { namespace graphics {
	class Layer
	{
	protected:
		std::string m_layer_name;
		std::vector<Entity> m_entities;
	public:
		Layer(const std::string &name);
		virtual ~Layer() = default;

		virtual void add_entity_object(Entity entity);
		virtual void remove_entity_object(Entity entity);
		virtual void on_update() = 0;
		// virtual void on_event(Event &e) = 0;

		const std::string& get_name() const { return m_layer_name; }
	};
}}
