#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include <GLFW/glfw3.h>
#include "../input/input.h"

namespace dream {

	Camera::Camera(float left, float right, float bottom, float top)
	{
		m_projection_mat = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_view_mat = glm::mat4(1.0f);
		m_view_projection_mat = m_projection_mat * m_view_mat;
    	dream::InputManager::get().bind_action(InputAction::MoveCameraUp, GLFW_KEY_UP);
		dream::InputManager::get().bind_action(InputAction::MoveCameraDown, GLFW_KEY_DOWN);
		dream::InputManager::get().bind_action(InputAction::MoveCameraLeft, GLFW_KEY_LEFT);
		dream::InputManager::get().bind_action(InputAction::MoveCameraRight, GLFW_KEY_RIGHT);
	}

	void Camera::on_update()
	{
		set_position(m_position);
		on_key_pressed();
	}

	bool Camera::on_key_pressed()
	{
		if (dream::InputManager::get().is_action_pressed(dream::InputAction::MoveCameraUp))
			m_position.y -= 0.1;
		if (dream::InputManager::get().is_action_pressed(dream::InputAction::MoveCameraDown))
			m_position.y += 0.1;
		if (dream::InputManager::get().is_action_pressed(dream::InputAction::MoveCameraLeft))
			m_position.x += 0.1;
		if (dream::InputManager::get().is_action_pressed(dream::InputAction::MoveCameraRight))
			m_position.x -= 0.1;

		return true;
	}

	bool Camera::on_mouse_moved()
	{
		// m_position.x += e.get_x() / 10000;
		// m_position.y += e.get_y() / 10000;

		return true;
	}

	bool Camera::on_mouse_scrolled()
	{
		return true;
	}

	void Camera::set_projection(float left, float right, float bottom, float top)
	{
		m_projection_mat = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_view_projection_mat = m_projection_mat * m_view_mat;
	}

	void Camera::recalculate_view_mat()
	{
		m_view_projection_mat = m_projection_mat * m_view_mat;
	}
}