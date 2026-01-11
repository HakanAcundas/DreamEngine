#include <string>
#include "renderer2D.hpp"
#include "game_layer.hpp"
#include "metric_utils.hpp"

using namespace dream;
using namespace graphics;

GameLayer::GameLayer(Shader& shader, Camera& camera)
	: Layer("GameLayer"), m_shader(shader), m_camera(camera)
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
