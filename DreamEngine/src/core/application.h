#pragma once
#include "../widow/window.h"
#include "../input/events/windowEvent.h"
#include "../input/input.h"
#include "../input/inputCodes/keyCodes.h"
#include "../input/events/keyEvent.h"
#include "../input/events/event.h"
#include <glfw/glfw3.h>

namespace dream {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
		void onEvent(Event& e);

		//void PushLayer(Layer* layer);
		//void PushOverlay(Layer* layer);

		Window& getWindow() { return *m_Window; }
		static Application& get() { return *s_application; }
	private:
		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_application;
	};

	//Application* createApplication();

}