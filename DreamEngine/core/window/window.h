#pragma once
#include <iostream>
//#include <GL/glew.h>
#include <glad/glad.h>
#include <functional>
#include <GLFW/glfw3.h>
#include "../events/event.h"

namespace dream {
	
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const char* title = "Dream Engine", int width = 1280, int height = 720, bool vsync = false);
		~Window();
		void Clear() const;
		void OnUpdate();
		
		int GetWidth() { return m_WindowData.width; }
		int GetHeight() { return m_WindowData.height; }
		const char* GetTitle() { return m_WindowData.title; }
		bool IsVsync() { return m_WindowData.vsync; }
		void SetVSync(bool mode);
		bool IsClosed() { return m_WindowData.closed; }
		GLFWwindow* GetGLFWwindow() const { return m_Window; }
		inline void SetEventCallback(const EventCallbackFn& callback) { m_WindowData.EventCallback = callback; }

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			const char* title;
			int width, height;
			bool vsync, closed = false;

			EventCallbackFn EventCallback;
		};

		WindowData m_WindowData;

	private:
		bool Init();
	};
}
