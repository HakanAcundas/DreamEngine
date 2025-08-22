#pragma once
#include <unordered_map>
#include <algorithm>
#include <glm/glm.hpp>

namespace dream {

	class Input
	{
	public:
		static void on_key_event(int key, int action);
		static void on_mouse_button_event(int button, int action);
		static void on_scroll(double xOffset, double yOffset);
		static void on_mouse_move(double xPos, double yPos);

		static bool is_key_pressed(int key);
		static bool is_mouse_button_pressed(int button);
		static glm::vec2 get_mouse_position();
		static glm::vec2 get_mouse_offset();
		static glm::vec2 get_scroll_offset();

		static void update();

	private:
		static std::unordered_map<int, bool> keyState;
		static std::unordered_map<int, bool> mouseButtonState;
		static glm::vec2 currentMousePos;
		static glm::vec2 lastMousePos;
		static glm::vec2 mouseOffset;
		static glm::vec2 scrollOffset;
	};
}

