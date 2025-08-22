#include "game_layer.h"

using namespace dream;
using namespace graphics;

GameLayer::GameLayer(Shader *shader)
	: Layer("GameLayer"), m_shader(shader)
{
	m_shader->enable();
	m_shader->set_uniformMat4("pr_matrix", m_projection_mat);
	m_shader->disable();
}

GameLayer::GameLayer(Shader *shader, Camera *camera)
	: Layer("GameLayer"), m_shader(shader), m_camera(camera)
{
	m_shader->enable();
	m_shader->set_uniformMat4("pr_matrix", camera->get_projection_mat());
	m_shader->set_uniformMat4("ml_matrix", glm::translate(camera->get_view_mat(), camera->get_position()));
	m_shader->set_uniform2f("light_pos", glm::vec2(0.0f, 0.0f));
	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};
	m_shader->set_uniform1iv("textures", texIDs, 10);
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
	m_shader->set_uniformMat4("pr_matrix", m_camera->get_projection_mat());
	m_shader->set_uniformMat4("ml_matrix", glm::translate(m_camera->get_view_mat(), m_camera->get_position()));
	m_shader->set_uniform2f("light_pos", m_light_pos);
	m_camera->on_update();
	set_camera(m_camera);
	on_mouse_moved();
	m_shader->enable();

	m_level.get_player()->draw();
	Renderer2D::get_instance()->draw_label("Hello World", glm::vec2(4.0f, 2.0f), "../DreamTest/assets/Fonts/Arial.ttf", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	Renderer2D::get_instance()->end();
	Renderer2D::get_instance()->flush();
}

bool GameLayer::on_mouse_moved()
{
	m_light_pos.x = (float)((double)Input::get_mouse_position().x * 16.0f/ 1280.0f);
	m_light_pos.y = (float)(9.0f - (double)Input::get_mouse_position().y * 9.0f / 720.0f);
	return true;
}

bool GameLayer::on_key_pressed()
{
	return true;
}
