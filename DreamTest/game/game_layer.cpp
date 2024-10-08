#include "game_layer.h"
#include "mouse_event.h"

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
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete &m_entities[i];
	}
}

void GameLayer::on_update()
{
	Renderer2D::get_singleton()->begin();
	m_shader->set_uniformMat4("pr_matrix", m_camera->get_projection_mat());
	m_shader->set_uniformMat4("ml_matrix", glm::translate(m_camera->get_view_mat(), m_camera->get_position()));
	m_shader->set_uniform2f("light_pos", m_light_pos);
	m_camera->on_update();
	set_camera(m_camera);
	m_shader->enable();
	for (Entity* entity : m_level.get_walls())
	{
		Renderer2D::get_singleton()->draw_renderable(entity->get_position(), entity->get_size(), entity->get_texture());
	}

	Renderer2D::get_singleton()->draw_renderable(m_level.get_player()->get_position(),
		m_level.get_player()->get_size(), m_level.get_player()->get_texture());

	for (Entity* entity : m_level.get_enemies())
	{
		Renderer2D::get_singleton()->draw_renderable(entity->get_position(), entity->get_size(), entity->get_sub_texture_2d());
	}

	Renderer2D::get_singleton()->end();
	Renderer2D::get_singleton()->flush();
}

void GameLayer::on_event(Event &e)
{
	m_camera->on_event(e);
	switch (e.get_event_type())
	{
	case Event::EventType::KEY_PRESSED:
		on_key_pressed(static_cast<KeyPressedEvent&>(e));
		break;
	case Event::EventType::MOUSE_MOVED:
		on_mouse_moved(static_cast<MouseMovedEvent&>(e));
		break;
	default:
		printf("Game Layer Unknown Event!!!");
	}
}

bool GameLayer::on_mouse_moved(MouseMovedEvent &e)
{
	if (!e.handled)
	{
		m_light_pos.x = (float)((double)e.get_x() * 16.0f/ 1280.0f);
		m_light_pos.y = (float)(9.0f - (double)e.get_y() * 9.0f / 720.0f);
	}
	return true;
}

bool GameLayer::on_key_pressed(KeyPressedEvent &e)
{
	glm::vec3 playerPos = m_level.get_player()->get_position();
	switch (e.get_keycode())
	{
	case 87:
		m_level.get_player()->set_position(playerPos.x + 0.02, playerPos.y, playerPos.z);
	}

	return true;
}
