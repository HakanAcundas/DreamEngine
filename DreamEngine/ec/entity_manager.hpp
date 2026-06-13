#pragma once

#include <array>
#include <queue>
#include "signature.hpp"
#include "entity.hpp"

class EntityManager
{
public:
	EntityManager();
	Entity create_entity();
	void destroy_entity(Entity entity);
	void set_signature(Entity entity, Signature signature);
	Signature get_signature(Entity entity);
private:
	std::queue<Entity> m_avaible_entities;
	std::array<Signature, MAX_ENTITIES> m_signatures;
	uint32_t m_living_entity_count = 0;
};
