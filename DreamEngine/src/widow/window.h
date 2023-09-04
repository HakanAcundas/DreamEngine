#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../input/keyCodes.h"

namespace dream { namespace window {
	class Window
	{
	private:
		GLFWwindow* window;
		int width, height;
		const char* title;
		bool vsync, closed;

		bool init();

	public:
		Window(const char* title, int width, int height, bool vsync);
		~Window();
		void clear() const;
		void update();
		void setVSync(bool mode);

		int getWidth() { return width; }
		int getHeight() { return height; }
		const char* getTitle() { return title; }
		bool isVsync() { return vsync; }
		bool isClosed() { return closed; }
	};
}}
