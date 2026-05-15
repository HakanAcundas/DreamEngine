#pragma once

#include <shader.hpp>
#include <camera.hpp>
#include <layer.hpp>
#include <event_dispatcher.hpp>
#include <ecs/components/transform.hpp>
#include <ecs/systems/physics_system.hpp>
#include <ecs/ecs_manager.hpp>

using namespace dream;
using namespace graphics;

class GameLayer : public Layer
{
private:
	Shader& m_shader;
	Camera& m_camera;
	ECSManager& m_ecsm;
	EventDispatcher& m_event_dispatcher;
	
	glm::mat4 m_projection_mat;
	glm::vec2 m_light_pos;
	std::shared_ptr<PhysicsSystem> physics_system;
	
	Entity player;
	float scale;
	const float dt = 0.1f;

public:
	GameLayer() = default;
	GameLayer(Shader& shader, Camera& camera, ECSManager& ecm, EventDispatcher& event_dispatcher);
	~GameLayer();

	void on_update() override;
	bool on_key_pressed();
	bool on_mouse_moved();

	// Getter & Setter
	Shader& get_shader() { return m_shader; }
	void set_camera(Camera& camera) { m_camera = camera; }
};
