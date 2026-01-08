#pragma once
#include <layer.hpp>

using namespace dream;
using namespace graphics;

class GameLayer : public Layer
{
private:
	Shader *m_shader;
	glm::mat4 m_projection_mat;
	glm::vec2 m_light_pos;
	unsigned int current_level = 0;
public:
	GameLayer(Shader *shader);

	GameLayer(std::string &vertex_shader, std::string &fragment_shader, Camera *camera);
	~GameLayer();

	void on_update() override;
	bool on_key_pressed();
	bool on_mouse_moved();
	Shader* get_shader() { return m_shader; }
};
