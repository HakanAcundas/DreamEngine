#include <assert.h>
#include "entity_manager.hpp"

EntityManager::EntityManager()
{
	for (Entity e = 0; e < MAX_ENTITIES; e++)
	{
		m_avaible_entities.push(e);
	}
}

Entity EntityManager::create_entity()
{
	assert(m_living_entity_count < MAX_ENTITIES && "Too many entities in existence.");

	Entity id = m_avaible_entities.front();
	m_avaible_entities.push(id);
	m_living_entity_count++;

	return id;
}

void EntityManager::destroy_entity(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	m_signatures[entity].reset();
	m_avaible_entities.push(entity);
	m_living_entity_count--;
}

Signature EntityManager::get_signature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	return m_signatures[entity];
}

void EntityManager::set_signature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	m_signatures[entity] = signature;
}
