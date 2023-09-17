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
		float vertices[] =
		{
			0, 0, 0,
			0, 3, 0,
			8, 3, 0,
			8 ,0, 0
		};

		unsigned short indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};


		float colors[] =
		{
			1, 0, 1, 1,
			1, 0, 1, 1,
			1, 0, 1, 1,
			1, 0, 1, 1
		};

		VertexArray vbo;
		IndexBuffer ibo(indices, 6);
		vbo.AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		vbo.AddBuffer(new Buffer(colors, 4 * 4, 4), 1);

		std::vector<int> keysTrack{ GLFW_KEY_ESCAPE ,GLFW_KEY_SPACE, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT };
		KeyInput inputHandlerEngine(keysTrack);
		inputHandlerEngine.setupKeyInputs(*m_Window);

		Shader shader("../DreamEngine/src/shaders/vertex.shader", "../DreamEngine/src/shaders/fragment.shader");
		shader.Enable();

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
			vbo.Bind();
			ibo.Bind();
			glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_SHORT, 0);
			
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

			ibo.Unbind();
			vbo.Unbind();

			float time = (float)glfwGetTime();
			m_LastFrameTime = time;
			m_Window->update();
		}
	}
}
