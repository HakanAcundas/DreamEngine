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
		// Singleton
		static Application* s_Application;

		bool m_Running = true;
		float m_LastFrame = 0.0f;
		std::shared_ptr<Window> m_Window;
		std::vector<std::shared_ptr<graphics::Layer>> m_Layers;
	
	public:
		Application();
		~Application();

		void Run();
		void OnEvent(Event& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		void PushLayer(graphics::Layer* layer);
		void PopLayer(graphics::Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& GetApplication() { return *s_Application; }
	};
}