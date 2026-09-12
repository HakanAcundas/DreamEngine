#pragma once

#include <dream/window/window.hpp>
#include <dream/ec/ec_manager.hpp>
#include <dream/renderer/renderer2D.hpp>
#include <dream/renderer/shader.hpp>
#include <dream/physics/physics_engine2D.hpp>
#include <dream/scene/layer.hpp>
#include <dream/events/event.hpp>
#include <dream/events/event_dispatcher.hpp>
#include <dream/camera/camera.hpp>
#include <memory>
#include <vector>

namespace dream
{
	using namespace graphics;

	class Application
	{
	public:
		Application();
		~Application();

		void run();
		void on_event(Event& event);
		bool on_key_pressed();
		void push_layer(std::shared_ptr<graphics::Layer> spLayer);
		void pop_layer(std::shared_ptr<graphics::Layer> spLayer);

		inline static Application& get_application() { return *s_application; }
		inline Window& get_window() { return *m_window; }
		inline Renderer2D& get_renderer() { return *m_renderer; }
		inline ECManager& get_ecs_manager() { return *m_ecm; }
		inline PhysicsEngine2D& get_physic_engine() { return *m_physics_engine; }
		inline EventDispatcher& get_event_dispatcher() { return *m_dispatcher; }

	private:
		// Singleton
		static Application *s_application;
		
		bool m_running = true;
		float m_last_frame = 0.0f;
		std::unique_ptr<Window> m_window;
		std::unique_ptr<Renderer2D> m_renderer;
		std::unique_ptr<ECManager> m_ecm;
		std::unique_ptr<PhysicsEngine2D> m_physics_engine;
		std::unique_ptr<EventDispatcher> m_dispatcher;

		std::vector<std::shared_ptr<graphics::Layer>> m_layers;
	};
}
