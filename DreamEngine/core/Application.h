#pragma once
#include <vector>
#include "window/Window.h"
#include "scene/Layer.h"
#include "scene/Renderer2D.h"

namespace dream
{
	class Application
	{
	private:
		bool m_Running = true;
		float m_LastFrame = 0.0f;
		Window* m_Window;
		std::vector<graphics::Layer*> m_Layers;
			
		// Singleton
		static Application* s_Application;

	public:
		Application();
		~Application();

		void Run();
		void OnEvent();
		void PushLayer(graphics::Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& GetApplication() { return *s_Application; }
	};
}