#pragma once
#include <glm/glm.hpp>
#include "../input/input_manager.h"

namespace dream {
	class Camera
	{
	private:
		glm::mat4 m_projection_mat;
		glm::mat4 m_view_mat;
		glm::mat4 m_view_projection_mat;
		glm::vec3 m_position;

		float m_rotation_angle;
		bool m_rotation;
		float m_camera_translation_speed = 5.0f, m_camera_rotation_speed = 180.0f;
		float m_aspect_ratio;
		float m_zoom_level = 1.0f;

		void recalculate_view_mat();
	public:
		Camera() = default;
		Camera(float left, float right, float bottom, float top);

		void on_update();
		bool on_key_pressed();
		bool on_mouse_moved();
		bool on_mouse_scrolled();

		// Getters and Setters
		void set_projection(float left, float right, float bottom, float top);

		const glm::vec3& get_position() const { return m_position; }
		void set_position(const glm::vec3 position) { m_position = position; }

		float get_rotation_angle() { return m_rotation_angle; }
		void set_rotation_angle(float rotation_angle) { m_rotation_angle = rotation_angle; }

		bool get_rotation() { return m_rotation; }
		void set_rotation(bool rotation) { m_rotation = rotation; }

		glm::mat4 get_projection_mat() { return m_projection_mat; }
		glm::mat4 get_view_mat() { return m_view_mat; }
		glm::mat4 get_projection_view_mat() { return m_view_projection_mat; }
	};
}
