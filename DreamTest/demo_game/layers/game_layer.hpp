#pragma once

#include <camera/camera.hpp>
#include <scene/layer.hpp>
#include <renderer/renderer2D.hpp>
#include <events/event_dispatcher.hpp>
#include <physics/physics_engine2D.hpp>
#include <ec/ec_manager.hpp>

using namespace dream;
using namespace graphics;

class GameLayer : public Layer
{
public:
	GameLayer() = default;
	GameLayer(
		Renderer2D& renderer,
		ECManager& ecm,
		PhysicsEngine2D& physics_engine,
		EventDispatcher& event_dispatcher
	);
	~GameLayer();

	void on_update() override;
	bool on_key_pressed();
	bool on_mouse_moved();

	// Getter & Setter
	void set_camera(Camera camera) { m_camera = camera; }

private:
	Renderer2D& m_renderer;
	Camera m_camera;
	ECManager& m_ecm;
	EventDispatcher& m_event_dispatcher;
	PhysicsEngine2D& m_physics_engine2D;

	glm::mat4 m_projection_mat;
	glm::vec2 m_light_pos = { 0.0f, 0.0f };

	Entity player;
	float scale;
	const float dt = 0.1f;
};
