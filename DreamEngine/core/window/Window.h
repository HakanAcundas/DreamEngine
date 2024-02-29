#pragma once
#include <iostream>
#include <GL/glew.h>
#include <functional>
#include <GLFW/glfw3.h>

namespace dream {
	class Window
	{
	private:
		GLFWwindow* m_Window;
		struct WindowData
		{
			const char* title;
			int width, height;
			bool vsync, closed = false;
		};
		WindowData m_WindowData;

	private:
		bool Init();

	public:
		Window(const char* title = "Dream Engine", int width = 1280, int height = 720, bool vsync = false);
		~Window();
		void Clear() const;
		void OnUpdate();
		void SetVSync(bool mode);
		
		int GetWidth() { return m_WindowData.width; }
		int GetHeight() { return m_WindowData.height; }
		const char* GetTitle() { return m_WindowData.title; }
		bool IsVsync() { return m_WindowData.vsync; }
		bool IsClosed() { return m_WindowData.closed; }
		GLFWwindow* GetGLFWwindow() const { return m_Window; }
	};
}
