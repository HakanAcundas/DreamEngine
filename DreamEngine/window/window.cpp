#include "window.hpp"
#include "../events/event.hpp"
#include "../events/event_dispatcher.hpp"

namespace dream {

	void resize(GLFWwindow *window, int width, int height);

	Window::Window(const char *title, int width, int height, bool vsync)
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
		glfwDestroyWindow(m_window);
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::runtime_error("Failed to Initialize GLFW!");
			return false;
		}

		m_window = glfwCreateWindow(width, height, title, NULL, NULL);

		if (!m_window)
		{
			std::runtime_error("Failed to Initialize GLFW Window!");
			return false;
		}
		glfwSetWindowUserPointer(m_window, this);
		set_vsync(true);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowSizeCallback(m_window, resize);
		glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
		{

		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods)
		{
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset)
		{
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xPos, double yPos)
		{
				Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

				MouseMovedEvent event(xPos, yPos);
				win->m_event_callback(event);
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
