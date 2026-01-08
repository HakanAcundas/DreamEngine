#pragma once

#include <shader.hpp>
#include <camera.hpp>
#include <layer.hpp>

using namespace dream;
using namespace graphics;

class GameLayer : public Layer
{
private:
	Shader& m_shader;
	Camera& m_camera;
	glm::mat4 m_projection_mat;
	glm::vec2 m_light_pos;
public:
	GameLayer() = default;
	GameLayer(Shader& shader, Camera& camera);
	~GameLayer();

	void on_update() override;
	bool on_key_pressed();
	bool on_mouse_moved();

	// Getter & Setter
	Shader& get_shader() { return m_shader; }
	void set_camera(Camera& camera) { m_camera = camera; }
};
