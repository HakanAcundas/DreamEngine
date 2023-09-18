#pragma once
#include "window/Window.h"
#include "input/KeyInput.h"
#include "input/inputCodes/KeyCodes.h"
#include "graphics/Shader.h"
#include "graphics/buffers/Buffer.h"
#include "graphics/buffers/IndexBuffer.h"
#include "graphics/buffers/VertexArray.h"
#include "graphics/Texture2D.h"
#include "graphics/renderer/Renderer2D.h"
#include "graphics/layers/Layer.h"
#include "graphics/layers/TileLayer.h"
#include "graphics/Camera.h"
#include <glfw/glfw3.h>

namespace dream {

	class Application
	{
	public:
		Application();
		~Application();

		void run();

		Window* getWindow() { return m_Window; }
	private:
		Window* m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		float r = 0;
	private:
	};

	//Application* createApplication();

}
