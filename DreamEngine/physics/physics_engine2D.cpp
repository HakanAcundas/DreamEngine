#include "physics_engine2D.hpp"
#include "../ecs/components/transform.hpp"
#include "../ecs/components/rigid_body.hpp"

PhysicsEngine2D::PhysicsEngine2D(ECSManager& ecsm)
{
	m_ecsm = std::make_shared<ECSManager>(ecsm);
}

void PhysicsEngine2D::apply_force(glm::vec2& force, const Entity& entity)
{
	RigidBody& rb = m_ecsm->get_component<RigidBody>(entity);
	float mass = rb.mass;
	glm::vec2 acc = force / mass;
	rb.velocity += acc * m_delta_time;
}

bool PhysicsEngine2D::check_collision(const Entity& a, const Entity& b, float radius)
{
	Transform& at = m_ecsm->get_component<Transform>(a);
	Transform& bt = m_ecsm->get_component<Transform>(b);

	glm::vec2 apos = glm::vec2(at.position.x, at.position.y);
	glm::vec2 bpos = glm::vec2(bt.position.x, bt.position.y);
	glm::vec2 distance = apos - bpos;

	return distance.length() < (2 * radius);
}

void PhysicsEngine2D::update(const Entity& entity)
{
	Transform& transform = m_ecsm->get_component<Transform>(entity);
	RigidBody& rigidbody = m_ecsm->get_component<RigidBody>(entity);

	transform.position += glm::vec3(rigidbody.velocity.x, rigidbody.velocity.y, 0) * m_delta_time;
}
