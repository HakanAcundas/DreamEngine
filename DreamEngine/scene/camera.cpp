#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include "../input/input.h"

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

	void Camera::on_event(Event &e)
	{
		switch (e.get_event_type())
		{
		case Event::EventType::KEY_PRESSED:
			on_key_pressed(static_cast<KeyPressedEvent&>(e));
		case Event::EventType::MOUSE_MOVED:
			on_mouse_moved(static_cast<MouseMovedEvent&>(e));
		case Event::EventType::MOUSE_SCROLLED:
			on_mouse_scrolled(static_cast<MouseScrolledEvent&>(e));
		}
	}

	bool Camera::on_key_pressed(KeyPressedEvent &e)
	{
		switch (e.get_keycode())
		{
		case DR_KEY_W:
			m_position.y -= 0.01;
		case DR_KEY_S:
			m_position.y += 0.01;
		case DR_KEY_A:
			m_position.x -= 0.01;
		case DR_KEY_D:
			m_position.x += 0.01;
		}

		return true;
	}

	bool Camera::on_mouse_moved(MouseMovedEvent &e)
	{
		m_position.x += e.get_x() / 10000;
		m_position.y += e.get_y() / 10000;

		return true;
	}

	bool Camera::on_mouse_scrolled(MouseScrolledEvent &e)
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