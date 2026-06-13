#pragma once

#include <memory>
#include "signature.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "component_manager.hpp"

class ECManager
{
public:
	void init()
	{
		m_component_manager = std::make_unique<ComponentManager>();
		m_entity_manager = std::make_unique<EntityManager>();
	}

	Entity create_entity()
	{
		return m_entity_manager->create_entity();
	}

	void destroy_entity(Entity entity)
	{
		m_entity_manager->destroy_entity(entity);
		m_component_manager->entity_destroyed(entity);
	}

	template<typename T>
	void register_component()
	{
		m_component_manager->register_component<T>();
	}

	template<typename T>
	void add_component(Entity entity, T component)
	{
		m_component_manager->add_component(entity, component);
		auto signature = m_entity_manager->get_signature(entity);
		signature.set(m_component_manager->get_component_type<T>(), true);
		m_entity_manager->set_signature(entity, signature);
	}

	template<typename T>
	ComponentType get_component_type()
	{
		return m_component_manager->get_component_type<T>();
	}

	template<typename T>
	T& get_component(Entity entity)
	{
		return m_component_manager->get_entity_component<T>(entity);
	}

private:
	std::shared_ptr<EntityManager> m_entity_manager;
	std::shared_ptr<ComponentManager> m_component_manager;
};
