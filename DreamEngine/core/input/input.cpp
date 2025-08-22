#include "../application.h"
#include "input.h"
#include <GLFW/glfw3.h>

namespace dream {

	std::unordered_map<int, bool> Input::keyState;
	std::unordered_map<int, bool> Input::mouseButtonState;
	glm::vec2 Input::currentMousePos(0.0f);
	glm::vec2 Input::lastMousePos(0.0f);
	glm::vec2 Input::mouseOffset(0.0f);
	glm::vec2 Input::scrollOffset(0.0f);

	void Input::on_key_event(int key, int action) {
		if (action == GLFW_PRESS)
			keyState[key] = true;
		else if (action == GLFW_RELEASE)
			keyState[key] = false;
	}

	void Input::on_mouse_button_event(int button, int action) {
		if (action == GLFW_PRESS)
			mouseButtonState[button] = true;
		else if (action == GLFW_RELEASE)
			mouseButtonState[button] = false;
	}

	void Input::on_scroll(double xOffset, double yOffset) {
		scrollOffset.x = static_cast<float>(xOffset);
		scrollOffset.y = static_cast<float>(yOffset);
	}

	void Input::on_mouse_move(double xPos, double yPos) {
		currentMousePos.x = static_cast<float>(xPos);
		currentMousePos.y = static_cast<float>(yPos);
	}

	bool Input::is_key_pressed(int key) {
		auto it = keyState.find(key);
		return it != keyState.end() && it->second;
	}

	bool Input::is_mouse_button_pressed(int button) {
		auto it = mouseButtonState.find(button);
		return it != mouseButtonState.end() && it->second;
	}

	glm::vec2 Input::get_mouse_position() {
		return currentMousePos;
	}

	glm::vec2 Input::get_mouse_offset() {
		return mouseOffset;
	}

	glm::vec2 Input::get_scroll_offset() {
		return scrollOffset;
	}

	void Input::update() {
		mouseOffset = currentMousePos - lastMousePos;
		lastMousePos = currentMousePos;
		scrollOffset = glm::vec2(0.0f); // Reset
	}
}