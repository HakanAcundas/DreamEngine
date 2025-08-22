#pragma once
#include <layer.h>
#include "test_level.h"

using namespace dream;
using namespace graphics;

class GameLayer : public Layer
{
private:
	Shader *m_shader;
	glm::mat4 m_projection_mat;
	Camera *m_camera;
	glm::vec2 m_light_pos;
	TestLevel m_level;
	unsigned int current_level = 0;
public:
	GameLayer(Shader *shader);
	GameLayer(Shader *shader, Camera *camera);

	GameLayer(std::string &vertex_shader, std::string &fragment_shader, Camera *camera);
	~GameLayer();

	void on_update() override;
	void on_event(Event &e) override;
	bool on_key_pressed(KeyPressedEvent &e);
	bool on_mouse_moved(MouseMovedEvent &e);
	void set_camera(Camera *camera) { m_camera = camera; }
	Shader* get_shader() { return m_shader; }
};
