#include "Input.h"
#include "../Application.h"
#include <GLFW/glfw3.h>

namespace dream {

	Input* Input::s_Input ;

	bool Input::IsKeyPressed(int keyCode)
	{
		auto* window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetGLFWwindow());
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetGLFWwindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetGLFWwindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}