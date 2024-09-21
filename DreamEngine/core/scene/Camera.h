#pragma once
#include <glm/glm.hpp>
#include "../events/MouseEvent.h"
#include "../events/KeyEvent.h"

namespace dream {
	class Camera
	{
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec3 m_Position;

		float m_RotationAngle;
		bool m_Rotation;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		void RecalculateViewMatrix();
	public:
		Camera() = default;
		Camera(float left, float right, float bottom, float top);

		void OnUpdate();
		void OnKeyPressed();
		void OnMouseMoved(const MouseMovedEvent& e);
		void OnMouseScrolled();

		// Getters and Setters
		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3 position) { m_Position = position; }

		float GetRotationAngle() { return m_RotationAngle; }
		void SetRotationAngle(float rotationAngle) { m_RotationAngle = rotationAngle; }

		bool GetRotation() { return m_Rotation; }
		void SetRotationAngle(bool rotation) { m_Rotation = rotation; }

		glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
		glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
		glm::mat4 GetProjectionViewMatrix() { return m_ViewProjectionMatrix; }
	};
}
