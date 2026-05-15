#include <random>
#include <string>
#include <log.hpp>
#include "renderer2D.hpp"
#include "game_layer.hpp"
#include "metric_utils.hpp"

using namespace dream;
using namespace graphics;

GameLayer::GameLayer(Shader& shader, Camera& camera, ECSManager& ecsm, EventDispatcher& event_dispatcher)
	: Layer("GameLayer"), m_shader(shader), m_camera(camera), m_ecsm(ecsm), m_event_dispatcher(event_dispatcher)
{
	m_shader.enable();
	m_shader.set_uniformMat4("pr_matrix", camera.get_projection_mat());
	m_shader.set_uniformMat4("ml_matrix", glm::translate(camera.get_view_mat(), camera.get_position()));
	m_shader.set_uniform2f("light_pos", glm::vec2(0.0f, 0.0f));
	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
	};
	m_shader.set_uniform1iv("textures", texIDs, 12);
	m_shader.disable();

	m_event_dispatcher.listen(EventType::MouseMovedEvent, std::bind(&Camera::on_event, m_camera, std::placeholders::_1));

	ecsm.register_component<Transform>();
	physics_system = ecsm.register_system<PhysicsSystem>();
	{
		Signature signature;
		signature.set(ecsm.get_component_type<Transform>());
		ecsm.set_system_signature<PhysicsSystem>(signature);
	};

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

	float scale = randScale(generator);
	const float dt = 0.1f;

	player = ecsm.create_entity();
	ecsm.add_component(player, Transform{
			.position = glm::vec3(randPosition(generator), randPosition(generator), randPosition(generator)),
			.rotation = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator)),
			.scale = glm::vec3(scale, scale, scale)
		});
}


GameLayer::~GameLayer()
{
	for (int i = 0; i < m_scene_objects.size(); i++)
	{
		delete &m_scene_objects[i];
	}
}

void GameLayer::on_update()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Renderer2D::get_instance()->begin();
	m_shader.set_uniformMat4("pr_matrix", m_camera.get_projection_mat());
	m_shader.set_uniformMat4("ml_matrix", glm::translate(m_camera.get_view_mat(), m_camera.get_position()));
	m_shader.set_uniform2f("light_pos", m_light_pos);
	m_camera.on_update();
	set_camera(m_camera);
	on_mouse_moved();
	m_shader.enable();
	unsigned int fps = get_FPS();
	Renderer2D::get_instance()->draw_label(std::to_string(fps), glm::vec2(0.0f, 8.5f), 0.010f, "assets/Fonts/Arial.ttf", glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
	Renderer2D::get_instance()->draw_label("Hello World!", glm::vec2(4.5f, 8.0f), 0.025f, "assets/Fonts/Arial.ttf", glm::vec4(1.0f, 1.0f, 0.5f, 0.0f));
	
	physics_system->update(dt, m_ecsm);
	Transform t = m_ecsm.get_component<Transform>(player);
	DREAM_LOG_TAG_INFO("GAME LAYER", "Position: x[{}], y[{}], z[{}]", t.position.x, t.position.y, t.position.z);

	Renderer2D::get_instance()->end();
	Renderer2D::get_instance()->flush();
}

bool GameLayer::on_mouse_moved()
{
	return true;
}

bool GameLayer::on_key_pressed()
{
	return true;
}
