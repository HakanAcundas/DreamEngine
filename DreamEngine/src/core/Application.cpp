#pragma once
#include "Application.h"


using namespace dream;
using namespace graphics;

#define SCREEN_WIDTH  960
#define SCREEN_HEIGHT 540

namespace dream {

	Application::Application()
	{
		//m_Window2 = new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT, false);
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

		std::vector<int> keysTrack{GLFW_KEY_ESCAPE ,GLFW_KEY_SPACE };
		KeyInput inputHandlerEngine(keysTrack);
		//KeyInput inputHandlerGame(keysTrack);
		inputHandlerEngine.setupKeyInputs(*m_Window);
		//inputHandlerGame.setupKeyInputs(*m_Window2);

		Shader shader("../DreamEngine/src/shaders/vertex.shader", "../DreamEngine/src/shaders/fragment.shader");
		shader.Enable();

		glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
		shader.SetUniformMat4("pr_matrix", ortho);
		shader.SetUniformMat4("ml_matrix", glm::translate(glm::mat4(1.0f), glm::vec3(4, 3, 0)));

		shader.SetUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
		shader.SetUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));

		while (m_Running)
		{
			m_Window->clear();
			vbo.Bind();
			ibo.Bind();
			glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_SHORT, 0);
			if (inputHandlerEngine.getIsKeyDown(GLFW_KEY_ESCAPE))
			{
				r = r + 0.01;
				std::cout << "SPACE! For ENGINE" << std::endl;
				m_Window->~Window();
				break;
			}
			else
				r = abs(r - 0.001);
			ibo.Unbind();
			vbo.Unbind();

			float time = (float)glfwGetTime();
			m_LastFrameTime = time;
			m_Window->update();
		}
	}
}
