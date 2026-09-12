#include <utils/log.hpp>
#include <renderer/renderer2D.hpp>
#include <ec/components/transform.hpp>
#include <ec/components/rigid_body.hpp>
#include "game_layer.hpp"
#include <utils/metric_utils.hpp>
#include <random>
#include <string>

using namespace dream;
using namespace graphics;

GameLayer::GameLayer(
	Renderer2D& renderer,
	ECManager& ecm,
	PhysicsEngine2D& physics_engine,
	EventDispatcher& event_dispatcher)
	: Layer("GameLayer"),
		m_renderer(renderer),
		m_ecm(ecm),
		m_event_dispatcher(event_dispatcher),
		m_physics_engine2D(physics_engine)
{
	m_camera = Camera(0.0f, 16.0f, 0.0f, 9.0f);
	m_event_dispatcher.listen(EventType::MouseMovedEvent, std::bind(&Camera::on_event, m_camera, std::placeholders::_1));

	ecm.register_component<Transform>();
	ecm.register_component<RigidBody>();

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

	float scale = randScale(generator);
	const float dt = 0.1f;

	player = ecm.create_entity();
	ecm.add_component(player, Transform{
			.position = glm::vec3(randPosition(generator), randPosition(generator), randPosition(generator)),
			.rotation = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator)),
			.scale = glm::vec3(scale, scale, scale)
		});
	ecm.add_component(player, RigidBody{
			.velocity = glm::vec2(0),
			.mass = 1.0f,
		});

	glm::vec2 gravity = glm::vec2(0.0f, 1.0f);
	m_physics_engine2D.apply_force(gravity, player);

	fill_quads();
}

GameLayer::~GameLayer()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete & m_entities[i];
	}
}

void GameLayer::on_update()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_renderer.begin_scene({ m_camera.get_projection_view_mat(), m_light_pos });
	m_camera.on_update();
	//m_renderer.draw_label("Hello World!", glm::vec2(4.5f, 8.0f), 0.025f, "assets/Fonts/Arial.ttf", glm::vec4(1.0f, 1.0f, 0.5f, 0.0f));
	draw_quads();
	m_renderer.end_scene();
	m_physics_engine2D.update(player);
	Transform t = m_ecm.get_component<Transform>(player);
}

bool GameLayer::on_mouse_moved()
{
	return true;
}

bool GameLayer::on_key_pressed()
{
	return true;
}

void GameLayer::fill_quads()
{
	for (float y = 0.0f; y < 9.0f; y += 0.5f)
	{
		for (float x = 0.0f; x < 16.0f; x += 0.5f)
		{
			unsigned color = std::rand() % 4;
			switch (color)
			{
			case 0: m_quads.push_back(glm::vec4(0, 0, 0, 1)); continue;
			case 1: m_quads.push_back(glm::vec4(1, 1, 1, 1)); continue;
			case 2: m_quads.push_back(glm::vec4(1, 0.92f, 0, 1)); continue;
			case 3: m_quads.push_back(glm::vec4(0, 0.1f, 0.4f, 1)); continue;
			}
		}
	}
}

void GameLayer::draw_quads()
{
	size_t i = 0;
	for (float y = 0.0f; y < 9.0f; y += 0.5f)
	{
		for (float x = 0.0f; x < 16.0f; x += 0.5f)
			m_renderer.draw_rect(glm::vec2(x, y), glm::vec2(0.5f, 0.5f), glm::vec4(m_quads[i++]));
	}
}