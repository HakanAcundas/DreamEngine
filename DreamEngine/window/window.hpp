#pragma once
#include <iostream>
//#include <GL/glew.h>
#include <glad/glad.h>
#include <functional>
#include <GLFW/glfw3.h>
#include "event.hpp"

namespace dream {
	
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		void set_event_callback(const EventCallbackFn& callback)
		{
			m_event_callback = callback;
		}

		Window(const char *title = "Dream Engine", int width = 1280, int height = 720, bool vsync = false);
		~Window();
		void clear() const;
		void on_update();
		
		int get_width() { return width; }
		int get_height() { return height; }
		const char* get_title() { return title; }
		bool is_vsync() { return vsync; }
		void set_vsync(bool mode);
		bool is_closed() { return closed; }
		GLFWwindow* get_glfw_window() const { return m_window; }

	private:
		GLFWwindow* m_window;
		EventCallbackFn m_event_callback;

		const char *title;
		int width, height;
		bool vsync, closed = false;

	private:
		bool init();
	};
}
