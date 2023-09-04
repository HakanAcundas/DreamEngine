#pragma once
#include <iostream>
#include <GL/glew.h>
#include <functional>
#include <GLFW/glfw3.h>
#include "../input/events/keyEvent.h"

namespace dream {
	class Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;
	private:
		GLFWwindow* window;
		struct WindowData
		{
			const char* title;
			int width, height;
			bool vsync, closed;
			EventCallback eventCallback;
		};
		bool init();
		WindowData m_WindowData;

	public:
		Window(const char* title, int width, int height, bool vsync);
		~Window();
		void clear() const;
		void update();
		void setVSync(bool mode);
		void setEventCallback(const EventCallback& callback);
		
		int getWidth() { return m_WindowData.width; }
		int getHeight() { return m_WindowData.height; }
		const char* getTitle() { return m_WindowData.title; }
		bool isVsync() { return m_WindowData.vsync; }
		bool isClosed() { return m_WindowData.closed; }
		void* getGLFWwindow() const { return window; }
	};
}
