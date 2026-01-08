#include <string>
#include "game_layer.hpp"
#include "metric_utils.hpp"

using namespace dream;
using namespace graphics;

GameLayer::GameLayer(Shader *shader)
	: Layer("GameLayer"), m_shader(shader)
{
	m_shader->enable();
	m_shader->set_uniformMat4("pr_matrix", m_projection_mat);
	m_shader->disable();
}

GameLayer::~GameLayer()
{
	delete m_shader;
	for (int i = 0; i < m_scene_objects.size(); i++)
	{
		delete &m_scene_objects[i];
	}
}

void GameLayer::on_update()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	Renderer2D::get_instance()->begin();
	on_mouse_moved();
	m_shader->enable();

	unsigned int fps = get_FPS();
	Renderer2D::get_instance()->draw_label(std::to_string(fps), glm::vec2(0.0f, 4.0f), 0.010f, "assets/Fonts/Arial.ttf", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Renderer2D::get_instance()->draw_label("Hello World!", glm::vec2(6.0f, 4.0f), 0.025f, "assets/Fonts/Arial.ttf", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
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
