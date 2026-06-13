#pragma once
#include <memory>
#include <assert.h>
#include <unordered_map>
#include "entity.hpp"
#include "component_array.hpp"

using ComponentType = std::uint8_t;

class ComponentManager
{
public:
	template<typename T>
	void register_component()
	{
		const char* type_name = typeid(T).name();
		assert(m_component_types.find(type_name) == m_component_types.end() && "Registering component type more than once.");

		m_component_types.insert({ type_name, m_next_component_type });
		++m_next_component_type;

		m_component_arrays.insert({ type_name, std::make_shared<ComponentArray<T>>() });
	}

	template<typename T>
	ComponentType get_component_type()
	{
		const char* type_name = typeid(T).name();
		assert(m_component_types.find(type_name) != m_component_types.end() && "Component not registered before use.");
		return m_component_types[type_name];
	}

	template<typename T>
	void add_component(Entity entity, T component)
	{
		get_component_array<T>()->insert_data(entity, component);
	}

	template<typename T>
	void remove_component(Entity entity)
	{
		get_component_array<T>()->remove_data(entity);
	}

	template<typename T>
	T& get_entity_component(Entity entity)
	{
		return get_component_array<T>()->get_data(entity);
	}

	void entity_destroyed(Entity entity)
	{
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : m_component_arrays)
		{
			auto const& component = pair.second;
			component->entity_destroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, ComponentType> m_component_types{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_component_arrays{};
	ComponentType m_next_component_type = 0;

	template<typename T>
	std::shared_ptr<ComponentArray<T>> get_component_array()
	{
		const char* typeName = typeid(T).name();

		assert(m_component_types.find(typeName) != m_component_types.end() && "Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(m_component_arrays[typeName]);
	}
};
