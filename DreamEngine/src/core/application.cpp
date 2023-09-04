#pragma once
#include "application.h"

namespace dream {
#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
	Application* Application::s_application = nullptr;

	Application::Application()
	{
		s_application = this;
		Window* window = new Window("Dream Engine", 1280, 780, false);
		window->setEventCallback(HZ_BIND_EVENT_FN(Application::onEvent));
	}

	Application::~Application()
	{
		
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::onWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::onWindowResize, this, std::placeholders::_1));
	}

	void Application::run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			m_LastFrameTime = time;
			m_Window->update();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::onWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		return false;
	}

}
