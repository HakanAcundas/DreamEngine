#include <random>
#include <string>
#include <log.hpp>
#include <renderer2D.hpp>
#include <ec/components/transform.hpp>
#include <ec/components/rigid_body.hpp>
#include "game_layer.hpp"
#include "metric_utils.hpp"

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
	m_shader = Shader("../DreamTest/shaders/vertex.shader", "../DreamTest/shaders/fragment.shader");
	m_camera = Camera(0.0f, 16.0f, 0.0f, 9.0f);

	m_shader.enable();
	m_shader.set_mat4("pr_matrix", m_camera.get_projection_mat());
	m_shader.set_mat4("ml_matrix", glm::translate(m_camera.get_view_mat(), m_camera.get_position()));
	m_shader.set_vec2("light_pos", glm::vec2(0.0f, 0.0f));
	m_shader.disable();

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
	m_shader.set_mat4("pr_matrix", m_camera.get_projection_mat());
	m_shader.set_mat4("ml_matrix", glm::translate(m_camera.get_view_mat(), m_camera.get_position()));
	m_shader.set_vec2("light_pos", m_light_pos);
	m_renderer.begin_scene(m_camera.get_projection_mat());
	m_camera.on_update();
	set_camera(m_camera);
	on_mouse_moved();
	m_shader.enable();
	unsigned int fps = get_FPS();
	//m_renderer.draw_label(std::to_string(fps), glm::vec2(0.0f, 8.5f), 0.010f, "assets/Fonts/Arial.ttf", glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
	//m_renderer.draw_label("Hello World!", glm::vec2(4.5f, 8.0f), 0.025f, "assets/Fonts/Arial.ttf", glm::vec4(1.0f, 1.0f, 0.5f, 0.0f));
	
	m_physics_engine2D.update(player);
	Transform t = m_ecm.get_component<Transform>(player);
	DREAM_LOG_TAG_INFO("GAME LAYER", "Player Position: x[{}], y[{}], z[{}]", t.position.x, t.position.y, t.position.z);
}

bool GameLayer::on_mouse_moved()
{
	return true;
}

bool GameLayer::on_key_pressed()
{
	return true;
}
