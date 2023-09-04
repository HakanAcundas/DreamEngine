#pragma once
#include <utility>

namespace dream { namespace input {
	class Input
	{
	public:
		Input();
	private:
		static bool isKeyPressed(int keyCode);
		static bool isMousePressed(int button);
		static std::pair<float, float> getMousePosition();
		static float getMouseX();
		static float getMouseY();
	};
}}
