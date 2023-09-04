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
		glfwDestroyWindow(window);
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to Initilized GLFW!";
			return false;
		}

		window = glfwCreateWindow(m_WindowData.width, m_WindowData.height, m_WindowData.title, NULL, NULL);

		if (!window)
		{
			std::cout << "Failed to Initilized GLFW Window!";
			return false;
		}

		setVSync(true);
		glfwMakeContextCurrent(window);
		glfwSetWindowSizeCallback(window, resize);
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, false);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					data.eventCallback(event);
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
		glfwGetFramebufferSize(window, &(m_WindowData.width), &(m_WindowData.height));
		glfwSwapBuffers(window);
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

	void Window::setEventCallback(const EventCallback& callback)
	{
		m_WindowData.eventCallback = callback;
	}

	void resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}