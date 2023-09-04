#pragma once
#include "../window/window.h"
#include "../input/keyInput.h"
#include "../input/inputCodes/keyCodes.h"
#include <glfw/glfw3.h>

namespace dream {

	class Application
	{
	public:
		Application();
		~Application();

		void run();

		//void PushLayer(Layer* layer);
		//void PushOverlay(Layer* layer);

		Window* getWindow() { return m_Window; }
		Window* getWindow2() { return m_Window2; }
	private:
		Window* m_Window;
		Window* m_Window2;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		float r = 0;
	private:
	};

	//Application* createApplication();

}