#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace dream { namespace graphics {

	Camera::Camera(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
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

	//void Camera::OnUpdate()
	//{

	//}

	//void Camera::OnKeyPressed()
	//{

	//}

	//void Camera::OnResize(float width, float height)
	//{

	//}

	//bool Camera::OnMouseScrolled()
	//{
	//	//m_ZoomLevel -= e.GetYOffset() * 0.25f;
	//	//m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	//	//SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	//	return false;
	//}

	//bool Camera::OnWindowResized()
	//{
	//	return false;
	//}
}}