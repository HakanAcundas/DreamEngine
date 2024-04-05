#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "../input/Input.h"

namespace dream {

	Camera::Camera(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::OnUpdate()
	{
		//const glm::vec2& mousePos = { Input::GetSingleton()->GetMouseX(), Input::GetSingleton()->GetMouseY()};
		//std::cout << "X: " << mousePos.x << " | Y: " << mousePos.y << "\n";
		OnKeyPressed();
		OnMouseScrolled();
		SetPosition(m_Position);
	}

	void Camera::OnKeyPressed()
	{
		if (Input::GetSingleton()->IsKeyPressed(DR_KEY_A))
		{
			m_Position.x += 00.1f;
		}
		else if (Input::GetSingleton()->IsKeyPressed(DR_KEY_D))
		{
			m_Position.x -= 00.1f;
		}

		if (Input::GetSingleton()->IsKeyPressed(DR_KEY_W))
		{
			m_Position.y -= 00.1f;
		}
		else if (Input::GetSingleton()->IsKeyPressed(DR_KEY_S))
		{
			m_Position.y += 00.1f;
		}
	}

	void Camera::OnMouseMoved(const MouseMovedEvent& e)
	{
		m_Position.x += e.GetX() / 10000;
		m_Position.y += e.GetY() / 10000;
	}

	void Camera::OnMouseScrolled()
	{
		/*m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);*/
	}

	void Camera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::RecalculateViewMatrix()
	{
		/*glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);*/
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}