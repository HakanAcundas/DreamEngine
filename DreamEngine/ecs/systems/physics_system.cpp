#include "physics_system.hpp"
#include "../components/transform.hpp"


void PhysicsSystem::update(const float& dt, ECSManager& ecsm)
{
	for (const Entity& entity : m_entities)
	{
		Transform& transform = ecsm.get_component<Transform>(entity);
		transform.position += 1 * dt;
	}
}
