#pragma once

#include <unordered_map>
#include "entity.hpp"

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

	}

	void remove_data(Entity entity)
	{

	}

	T& get_data(Entity entity)
	{

	}

	void entity_destroyed(Entity entity)
	{

	}

private:
	std::array<T, MAX_ENTITIES> m_component_array;
	std::unordered_map<Entity, size_t> m_entity_to_index_map;
	std::unordered_map<size_t, Entity> m_index_to_entity_map;
};
