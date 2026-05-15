#pragma once

#include <unordered_map>
#include "entity.hpp"
#include <assert.h>

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void entity_destroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : IComponentArray
{
public:
	void insert_data(Entity entity, T component)
	{
		assert(m_entity_to_index_map.find(entity) == m_entity_to_index_map.end() && "Component added to same entity more than once.");

		size_t new_index = m_size;
		m_entity_to_index_map[entity] = new_index;
		m_index_to_entity_map[new_index] = entity;
		m_component_array[new_index] = component;
		++m_size;
	}

	void remove_data(Entity entity)
	{
		assert(m_entity_to_index_map.find(entity) != m_entity_to_index_map.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t index_of_removed_entity = m_entity_to_index_map[entity];
		size_t index_of_last_element = m_size - 1;
		m_component_array[index_of_removed_entity] = m_component_array[index_of_last_element];

		// Update map to point to moved spot
		Entity entity_of_last_element = m_index_to_entity_map[index_of_last_element];
		m_entity_to_index_map[entity_of_last_element] = index_of_removed_entity;
		m_index_to_entity_map[index_of_removed_entity] = entity_of_last_element;

		m_entity_to_index_map.erase(entity);
		m_index_to_entity_map.erase(index_of_last_element);

		--m_size;
	}

	T& get_data(Entity entity)
	{
		assert(m_entity_to_index_map.find(entity) != m_entity_to_index_map.end() && "Retrieving non-existent component.");

		size_t index = m_entity_to_index_map[entity];
		return m_component_array[index];
	}

	void entity_destroyed(Entity entity)
	{
		if (m_entity_to_index_map.find(entity) != m_entity_to_index_map.end())
		{
			// Remove the entity's component if it existed
			remove_data(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> m_component_array;
	std::unordered_map<Entity, size_t> m_entity_to_index_map;
	std::unordered_map<size_t, Entity> m_index_to_entity_map;
	size_t m_size;
};
