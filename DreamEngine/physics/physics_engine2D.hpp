#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "../ecs/entity.hpp"
#include "../ecs/ecs_manager.hpp"


class PhysicsEngine2D
{
public:
	PhysicsEngine2D() = default;
	PhysicsEngine2D(ECSManager& ecsm);

	bool check_collision(const Entity& a, const Entity& b, float radius);
	void apply_force(glm::vec2& force, const Entity& entity);
	void update(const Entity& entity);

private:
	std::shared_ptr<ECSManager> m_ecsm;
	float m_delta_time = 0.016f; // 60 FPS
};
