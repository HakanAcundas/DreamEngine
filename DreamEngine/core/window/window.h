#pragma once
#include <iostream>
//#include <GL/glew.h>
#include <glad/glad.h>
#include <functional>
#include <GLFW/glfw3.h>

namespace dream {
	
	class Window
	{
	public:
		Window(const char *title = "Dream Engine", int width = 1280, int height = 720, bool vsync = false);
		~Window();
		void clear() const;
		void on_update();
		
		int get_width() { return m_window_data.width; }
		int get_height() { return m_window_data.height; }
		const char* get_title() { return m_window_data.title; }
		bool is_vsync() { return m_window_data.vsync; }
		void set_vsync(bool mode);
		bool is_closed() { return m_window_data.closed; }
		GLFWwindow* get_glfw_window() const { return m_window; }

	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			const char *title;
			int width, height;
			bool vsync, closed = false;
		};

		WindowData m_window_data;

	private:
		bool init();
	};
}
