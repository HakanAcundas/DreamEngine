#pragma once
#include "Game.h"


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
		Renderer2D::GetSingleton()->Init();

		std::vector<int> keysTrack{ GLFW_KEY_ESCAPE ,GLFW_KEY_SPACE, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT };
		KeyInput inputHandlerEngine(keysTrack);
		inputHandlerEngine.setupKeyInputs(*m_Window);

		Camera camera(-16.0f, 16.0f, -9.0f, 9.0f);
		camera.SetPosition(glm::vec3(4, 3, 0));

		Shader* shader = new Shader(
			"../DreamEngine/src/shaders/vertex.shader",
			"../DreamEngine/src/shaders/fragment.shader");
		GameLayer testLayer(shader, &camera);

		Texture2D* textures[] =
		{
			new Texture2D("images/test1.png"),
			new Texture2D("images/test2.png"),
			new Texture2D("images/test3.png"),
			new Texture2D("images/test4.png"),
			new Texture2D("images/test7.png")
		};

		for (float y = -9.0f; y < 9.0f; y++)
		{
			for (float x = -16.0f; x < 16.0f; x++)
			{
				testLayer.AddRenderable(new Renderable(glm::vec3(x, y, 1), glm::vec2(0.9f, 0.9f), textures[rand() % 5]));
			}
		}
		testLayer.AddRenderable(new Renderable(glm::vec3(-10, -3, 1), glm::vec2(6.0f, 6.0f), textures[1]));
		testLayer.AddRenderable(new Renderable(glm::vec3(10, 3, 1), glm::vec2(6.0f, 6.0f), textures[2]));

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
				position.y -= 0.01f;
				camera.SetPosition(position);
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_DOWN))
			{
				glm::vec3 position = camera.GetPosition();
				position.y += 0.01f;
				camera.SetPosition(position);
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_LEFT))
			{
				glm::vec3 position = camera.GetPosition();
				position.x += 0.01f;
				camera.SetPosition(position);
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_RIGHT))
			{
				glm::vec3 position = camera.GetPosition();
				position.x -= 0.01f;
				camera.SetPosition(position);
			}
			
			testLayer.SetCamera(&camera);
			testLayer.Render();
			m_Window->update();
		}
	}
}
