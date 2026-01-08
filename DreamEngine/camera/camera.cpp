#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "camera.hpp"
#include "log.hpp"

namespace dream {

	Camera::Camera(float left, float right, float bottom, float top)
	{
		m_projection_mat = glm::ortho(left, right, bottom, top);
		m_view_mat = glm::translate(glm::mat4(1.0f), -m_position);
		m_view_projection_mat = m_projection_mat * m_view_mat;
	}

	void Camera::on_update()
	{

	}

	// Event Functions
	void Camera::on_event(Event& event)
	{
		EventType type = event.get_type();
		switch (type)
		{
		case EventType::MouseMovedEvent:
			on_mouse_moved(static_cast<MouseMovedEvent&>(event));
			break;
		}
	}

	void Camera::on_key_pressed(KeyPressedEvent& event)
	{

	}

	void Camera::on_key_released(KeyReleasedEvent& event)
	{

	}

	void Camera::on_mouse_moved(MouseMovedEvent& event)
	{
		DREAM_LOG_TAG_ERROR("CAMERA", "on_mouse_moved");
	}

	void Camera::on_mouse_scrolled()
	{

	}

	void Camera::set_projection(float left, float right, float bottom, float top)
	{

	}
}