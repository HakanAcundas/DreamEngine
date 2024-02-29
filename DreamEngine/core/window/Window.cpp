#include "Window.h"
#include "../input/Input.h"

namespace dream {

	void Resize(GLFWwindow* window, int width, int height);

	Window::Window(const char* title, int width, int height, bool vsync)
	{
		this->m_WindowData.title = title;
		this->m_WindowData.width = width;
		this->m_WindowData.height = height;
		this->m_WindowData.vsync = vsync;

		if (!Init())
			glfwTerminate();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
	}

	bool Window::Init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to Initialize GLFW!";
			return false;
		}

		m_Window = glfwCreateWindow(m_WindowData.width, m_WindowData.height, m_WindowData.title, NULL, NULL);

		if (!m_Window)
		{
			std::cout << "Failed to Initialize GLFW Window!";
			return false;
		}

		SetVSync(true);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowSizeCallback(m_Window, Resize);
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					break;
				}
				case GLFW_RELEASE:
				{
					break;
				}
				case GLFW_REPEAT:
				{
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					break;
				}
				case GLFW_RELEASE:
				{
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		});

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to Initialize GLEW!";
			return false;
		}
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

		return true;
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::SetVSync(bool mode)
	{
		if (mode)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void Resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}
