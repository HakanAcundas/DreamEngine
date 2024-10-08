#include "../application.h"
#include "input.h"
#include <GLFW/glfw3.h>

namespace dream {

	Input *Input::s_input ;

	bool Input::is_key_pressed(int keycode)
	{
		auto* window = static_cast<GLFWwindow*>(Application::get_application().get_window().get_glfw_window());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS;
	}

	bool Input::is_mouse_button_pressed(const MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::get_application().get_window().get_glfw_window());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::get_mouse_position()
	{
		auto* window = static_cast<GLFWwindow*>(Application::get_application().get_window().get_glfw_window());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::get_mouse_x()
	{
		return get_mouse_position().x;
	}

	float Input::get_mouse_y()
	{
		return get_mouse_position().y;
	}
}