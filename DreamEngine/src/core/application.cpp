#pragma once
#include "application.h"

namespace dream {

	Application::Application()
	{
		m_Window2 = new Window("Game", 780, 780, false);
		m_Window = new Window("Dream Engine", 780, 780, false);
	}

	Application::~Application()
	{
		
	}

	void Application::run()
	{
		std::vector<int> keysTrack{ GLFW_KEY_SPACE, GLFW_KEY_1 };
		KeyInput inputHandlerEngine(keysTrack);
		KeyInput inputHandlerGame(keysTrack);
		inputHandlerEngine.setupKeyInputs(*m_Window);
		inputHandlerGame.setupKeyInputs(*m_Window2);

		while (m_Running)
		{
			m_Window->clear();
			m_Window2->clear();
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_SPACE))
			{
				r = r + 0.01;
				std::cout << "SPACE! For ENGINE" << std::endl;
			}
			else
				r = abs(r - 0.001);

			if (inputHandlerGame.getIsKeyDown(GLFW_KEY_1))
			{
				r = r + 0.01;
				std::cout << "1 FOR GAME!" << std::endl;
			}
			

			glClearColor(r, 0.5, 0.5, 1.0);
			float time = (float)glfwGetTime();
			m_LastFrameTime = time;
			m_Window->update();
			m_Window2->update();
		}
	}
}
