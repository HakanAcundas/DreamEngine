#pragma once
#include <iostream>
#include <GL/glew.h>
#include <functional>
#include <GLFW/glfw3.h>

namespace dream {
	class Window
	{
	public:
	private:
		GLFWwindow* m_Window;
		struct WindowData
		{
			const char* title;
			int width, height;
			bool vsync, closed = false;
		};
		bool init();
		WindowData m_WindowData;

	public:
		Window(const char* title = "Dream Engine", int width = 1280, int height = 720, bool vsync = false);
		~Window();
		void clear() const;
		void update();
		void setVSync(bool mode);
		
		int getWidth() { return m_WindowData.width; }
		int getHeight() { return m_WindowData.height; }
		const char* getTitle() { return m_WindowData.title; }
		bool isVsync() { return m_WindowData.vsync; }
		bool isClosed() { return m_WindowData.closed; }
		GLFWwindow* getGLFWwindow() const { return m_Window; }
	};
}
