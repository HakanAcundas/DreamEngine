#pragma once
#include <glm/glm.hpp>

namespace dream { namespace graphics {
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
		//bool OnMouseScrolled();
		//bool OnWindowResized();
	public:
		Camera() = default;
		Camera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		// Getters and Setters
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3 poisiton) { m_Position = poisiton; }

		float GetRotationAngle() { return m_RotationAngle; }
		void SetRotationAngle(float rotationAngle) { m_RotationAngle = rotationAngle; }

		bool GetRotation() { return m_Rotation; }
		void SetRotationAngle(bool rotation) { m_Rotation = rotation; }

		//// Camera Events
		//void OnUpdate();
		//void OnKeyPressed();
		//void OnResize(float width, float height);

		glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
		glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
		glm::mat4 GetProjectionViewMatrix() { return m_ViewProjectionMatrix; }


	};
}}
