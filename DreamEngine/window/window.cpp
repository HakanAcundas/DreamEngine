#include "window.h"
#include "../input/input.h"

namespace dream {

	void resize(GLFWwindow *window, int width, int height);

	Window::Window(const char *title, int width, int height, bool vsync)
	{
		this->m_window_data.title = title;
		this->m_window_data.width = width;
		this->m_window_data.height = height;
		this->m_window_data.vsync = vsync;

		if (!init())
			glfwTerminate();
	}    

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::runtime_error("Failed to Initialize GLFW!");
			return false;
		}

		m_window = glfwCreateWindow(m_window_data.width, m_window_data.height, m_window_data.title, NULL, NULL);

		if (!m_window)
		{
			std::runtime_error("Failed to Initialize GLFW Window!");
			return false;
		}
		glfwSetWindowUserPointer(m_window, &m_window_data);
		set_vsync(true);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowSizeCallback(m_window, resize);
		glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			dream::Input::on_key_event(key, action);
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods)
		{
			dream::Input::on_mouse_button_event(button, action);
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset)
		{
			dream::Input::on_scroll(xOffset, yOffset);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xPos, double yPos)
		{
			dream::Input::on_mouse_move(xPos, yPos);
		});


		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::runtime_error("Failed to initialize GLAD");
			return -1;
		}
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

		return true;
	}

	void Window::on_update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::set_vsync(bool mode)
	{
		if (mode)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void resize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}
