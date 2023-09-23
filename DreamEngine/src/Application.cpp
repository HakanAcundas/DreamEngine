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

		Texture2D* testTexture = new Texture2D("../images/test.png");

		Shader shader("../DreamEngine/src/shaders/vertex.shader", "../DreamEngine/src/shaders/fragment.shader");
		shader.Enable();

		Renderer2D* renderer = new Renderer2D();
		TileLayer layer(&shader);
		layer.AddRenderable(new Renderable(glm::vec3(0, 0, 2), glm::vec2(1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)));

		Camera camera(0.0f, 16.0f, 0.0f, 9.0f);
		camera.SetPosition(glm::vec3(4, 3, 0));
		shader.SetUniformMat4("pr_matrix", camera.GetProjectionMatrix());
		shader.SetUniformMat4("ml_matrix", glm::translate(camera.GetViewMatrix(), camera.GetPosition()));

		shader.SetUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
		shader.SetUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));

		while (m_Running)
		{
			m_Window->clear();
			shader.SetUniformMat4("ml_matrix", glm::translate(camera.GetViewMatrix(), camera.GetPosition()));
			
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_ESCAPE))
			{
				m_Window->~Window();
				break;
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_UP))
			{
				glm::vec3 position= camera.GetPosition();
				position.y -= 0.001f;
				camera.SetPosition(position);
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_DOWN))
			{
				glm::vec3 position = camera.GetPosition();
				position.y += 0.001f;
				camera.SetPosition(position);
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_LEFT))
			{
				glm::vec3 position = camera.GetPosition();
				position.x += 0.001f;
				camera.SetPosition(position);
			}
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_RIGHT))
			{
				glm::vec3 position = camera.GetPosition();
				position.x -= 0.001f;
				camera.SetPosition(position);
			}

			//layer.Render();
			float time = (float)glfwGetTime();
			m_LastFrameTime = time;
			m_Window->update();
		}
	}
}
