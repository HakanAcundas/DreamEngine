#pragma once

#include <shader.hpp>
#include <camera.hpp>
#include <layer.hpp>
#include <event_dispatcher.hpp>
#include <physics/physics_engine2D.hpp>
#include <ecs/ecs_manager.hpp>

using namespace dream;
using namespace graphics;

class GameLayer : public Layer
{
public:
	GameLayer() = default;
	GameLayer(Shader& shader, Camera& camera, ECSManager& ecm, EventDispatcher& event_dispatcher, PhysicsEngine2D& physics_engine2D);
	~GameLayer();

	void on_update() override;
	bool on_key_pressed();
	bool on_mouse_moved();

	// Getter & Setter
	Shader& get_shader() { return m_shader; }
	void set_camera(Camera& camera) { m_camera = camera; }

private:
	Shader& m_shader;
	Camera& m_camera;
	ECSManager& m_ecsm;
	EventDispatcher& m_event_dispatcher;
	PhysicsEngine2D& m_physics_engine2D;

	glm::mat4 m_projection_mat;
	glm::vec2 m_light_pos;

	Entity player;
	float scale;
	const float dt = 0.1f;
};
