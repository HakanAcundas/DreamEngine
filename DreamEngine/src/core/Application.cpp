#pragma once
#include "Application.h"

using namespace dream;
using namespace graphics;

#define SCREEN_WIDTH  960
#define SCREEN_HEIGHT 540

namespace dream {

	Application::Application()
	{
		m_Window2 = new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT, false);
		m_Window = new Window("Dream Engine", SCREEN_WIDTH, SCREEN_HEIGHT, false);
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

		Shader shader("../shaders/vertex.shader", "../shaders/fragment.shader");
		shader.Enable();

		glm::mat4 orthographic = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
		shader.SetUniformMat4("pr_matrix", orthographic);

		shader.SetUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
		shader.SetUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));


		while (m_Running)
		{
			m_Window->clear();
			m_Window2->clear();

			shader.SetUniform2f("light_pos", glm::vec2((float)(16.0f / (float)SCREEN_WIDTH), (float)(9.0f / (float)SCREEN_HEIGHT)));
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
