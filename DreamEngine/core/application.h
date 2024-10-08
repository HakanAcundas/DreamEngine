#pragma once
#include <vector>
#include "window/window.h"
#include "scene/layer.h"
#include "scene/renderer2D.h"

namespace dream
{
	class Application
	{
	private:
		// Singleton
		static Application *s_application;

		bool m_running = true;
		float m_last_frame = 0.0f;
		std::shared_ptr<Window> m_window;
		std::vector<graphics::Layer*> m_layers;
	
	public:
		Application();
		~Application();

		void run();
		void on_event(Event &e);
		bool on_key_pressed(KeyPressedEvent &e);
		void push_layer(graphics::Layer *layer);
		void pop_layer(graphics::Layer *layer);

		inline Window& get_window() { return *m_window; }
		inline static Application& get_application() { return *s_application; }
	};
}