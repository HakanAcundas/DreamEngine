#include "input.h"
#include "../core/application.h"
#include <GLFW/glfw3.h>

using namespace dream;

namespace dream { namespace input {

	bool Input::isKeyPressed(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getGLFWwindow());
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::isMousePressed(int button)
	{
		return true;
	}

	std::pair<float, float> Input::getMousePosition()
	{
		std::pair<float, float> a = { 1.0, 1.0 };
		return a;
	}

	float Input::getMouseX()
	{
		return 0.0;
	}

	float Input::getMouseY()
	{
		return 0.0;
	}
}}
