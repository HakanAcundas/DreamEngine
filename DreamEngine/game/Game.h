#pragma once
#include "../src/window/Window.h"
#include "../src/input/KeyInput.h"
#include "../src/input/inputCodes/KeyCodes.h"
#include "GameLayer.h"
#include <glfw/glfw3.h>

namespace dream {

	class Application
	{
	public:
		Application();
		~Application();

		void run();

		Window* getWindow() { return m_Window; }
	private:
		Window* m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		float r = 0;
	private:
	};
}
