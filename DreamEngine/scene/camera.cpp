#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "camera.hpp"

namespace dream {

	Camera::Camera(float left, float right, float bottom, float top)
	{
		m_projection_mat = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_view_mat = glm::mat4(1.0f);
		m_view_projection_mat = m_projection_mat * m_view_mat;
	}

	void Camera::on_update()
	{
		set_position(m_position);
	}

	// Event Functions
	void Camera::on_event(Event& event)
	{

	}

	void Camera::on_key_pressed(KeyPressedEvent& event)
	{

	}

	void Camera::on_key_released(KeyReleasedEvent& event)
	{

	}

	void Camera::on_mouse_moved(MouseMovedEvent& event)
	{

	}

	void Camera::on_mouse_scrolled()
	{

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