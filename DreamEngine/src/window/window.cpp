#include "window.h"

namespace dream {

	void resize(GLFWwindow* window, int width, int height);

	Window::Window(const char* title, int width, int height, bool vsync)
	{
		this->m_WindowData.title = title;
		this->m_WindowData.width = width;
		this->m_WindowData.height = height;
		this->m_WindowData.vsync = vsync;

		if (!init())
			glfwTerminate();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to Initilized GLFW!";
			return false;
		}

		m_Window = glfwCreateWindow(m_WindowData.width, m_WindowData.height, m_WindowData.title, NULL, NULL);

		if (!m_Window)
		{
			std::cout << "Failed to Initilized GLFW Window!";
			return false;
		}

		setVSync(true);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowSizeCallback(m_Window, resize);
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

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to Initilized GLEW!";
			return false;
		}
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

		return true;
	}

	void Window::update()
	{
		glfwPollEvents();
		glfwGetFramebufferSize(m_Window, &(m_WindowData.width), &(m_WindowData.height));
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.5, -0.5);
		glEnd();
		glfwSwapBuffers(m_Window);
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::setVSync(bool mode)
	{
		if (mode)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}