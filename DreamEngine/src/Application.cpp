#pragma once
#include "Application.h"


using namespace dream;
using namespace graphics;

#define SCREEN_WIDTH  960
#define SCREEN_HEIGHT 540

namespace dream {

	Application::Application()
	{
		m_Window = new Window("Dream Engine", SCREEN_WIDTH, SCREEN_HEIGHT, false);
	}

	Application::~Application()
	{
		
	}

	void Application::run()
	{
		std::vector<int> keysTrack{ GLFW_KEY_ESCAPE ,GLFW_KEY_SPACE, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT };
		KeyInput inputHandlerEngine(keysTrack);
		inputHandlerEngine.setupKeyInputs(*m_Window);

		//Texture2D* testTexture = new Texture2D("../images/test.png");

		Camera camera(-16.0f, 16.0f, -9.0f, 9.0f);
		camera.SetPosition(glm::vec3(4, 3, 0));

		Shader* shader = new Shader(
			"../DreamEngine/src/shaders/vertex.shader",
			"../DreamEngine/src/shaders/fragment.shader");
		TileLayer testLayer(shader, camera);
		testLayer.AddRenderable(new Renderable(glm::vec3(1, 0, 2), glm::vec2(1.0f, 1.0f), glm::vec4(0.31f, 1.0f, 1.0f, 1.0f)));
		testLayer.AddRenderable(new Renderable(glm::vec3(0, 0, 2), glm::vec2(1.0f, 1.0f), glm::vec4(0.31f, 1.0f, 1.0f, 1.0f)));

		while (m_Running)
		{
			m_Window->clear();
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_ESCAPE))
			{
				m_Window->~Window();
				break;
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_UP))
			{
				glm::vec3 position= camera.GetPosition();
				position.y -= 0.005f;
				camera.SetPosition(position);
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_DOWN))
			{
				glm::vec3 position = camera.GetPosition();
				position.y += 0.005f;
				camera.SetPosition(position);
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_LEFT))
			{
				glm::vec3 position = camera.GetPosition();
				position.x += 0.005f;
				camera.SetPosition(position);
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_RIGHT))
			{
				glm::vec3 position = camera.GetPosition();
				position.x -= 0.005f;
				camera.SetPosition(position);
			}
			glClearColor(0.5, 0.5, 0.5, 1.0);
			
			testLayer.SetCamera(camera);
			testLayer.Render();
			float time = (float)glfwGetTime();
			m_LastFrameTime = time;
			m_Window->update();
		}
	}
}
