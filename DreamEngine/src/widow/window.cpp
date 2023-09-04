#include "window.h"

namespace dream { namespace window {

	void resize(GLFWwindow* window, int width, int height);

	Window::Window(const char* title, int width, int height, bool vsync)
	{
		this->title = title;
		this->width = width;
		this->height = height;
		this->vsync = vsync;

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

		window = glfwCreateWindow(width, height, title, NULL, NULL);

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
			switch (action)
			{
				case GLFW_PRESS:
				{
					std::cout << "Key Pressed: " << glfwGetKeyName(key, scancode) << std::endl;
					break;
				}
				case GLFW_RELEASE:
				{
					std::cout << "Key Released: " << glfwGetKeyName(key, scancode) << std::endl;
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
		glfwGetFramebufferSize(window, &width, &height);
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

	void resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}}