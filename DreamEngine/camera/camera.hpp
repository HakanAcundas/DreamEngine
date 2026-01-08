#pragma once
#include <glm/glm.hpp>
#include "../events/event.hpp"

namespace dream {
	class Camera
	{
	public:
		Camera() = default;
		Camera(float left, float right, float bottom, float top);

		void on_update();

		// Event Functions
		void on_event(Event& event);
		void on_key_pressed(KeyPressedEvent& event);
		void on_key_released(KeyReleasedEvent& event);
		void on_mouse_moved(MouseMovedEvent& event);
		void on_mouse_scrolled();

		// Getters and Setters
		void set_projection(float left, float right, float bottom, float top);

		const glm::vec3& get_position() const { return m_position; }
		void set_position(const glm::vec3 position) { m_position = position; }

		glm::mat4 get_projection_mat() { return m_projection_mat; }
		glm::mat4 get_view_mat() { return m_view_mat; }
		glm::mat4 get_projection_view_mat() { return m_view_projection_mat; }

	private:
		glm::mat4 m_projection_mat;
		glm::mat4 m_view_mat;
		glm::mat4 m_view_projection_mat;
		glm::vec3 m_position;
	};
}
