#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "../ec/entity.hpp"
#include "../ec/ec_manager.hpp"


class PhysicsEngine2D
{
public:
	PhysicsEngine2D() = default;
	PhysicsEngine2D(ECManager& ecsm);

	bool check_collision(const Entity& a, const Entity& b, float radius);
	void apply_force(glm::vec2& force, const Entity& entity);
	void update(const Entity& entity);

private:
	std::shared_ptr<ECManager> m_ecm;
	float m_delta_time = 0.016f; // 60 FPS
};
