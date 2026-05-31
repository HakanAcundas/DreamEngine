#pragma once

#include <vector>
#include "window/window.hpp"
#include "ecs/ecs_manager.hpp"
#include "renderer/renderer2D.hpp"
#include "renderer/resources/shader.hpp"
#include "physics/physics_engine2D.hpp"
#include "scene/layer.hpp"
#include "events/event.hpp"
#include "events/event_dispatcher.hpp"
#include "camera/camera.hpp"

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
		void push_layer(graphics::Layer* layer);
		void pop_layer(graphics::Layer* layer);
		
		void set_shader(Shader& shader)	{ m_shader = shader; }
		void set_camera(Camera& camera)	{ m_camera = camera; }

		inline Window& get_window() { return *m_window; }
		inline static Application& get_application() { return *s_application; }
		inline Shader& get_shader() { return m_shader; }
		inline Camera& get_camera() { return m_camera; }
		inline ECSManager& get_ecs_manager() { return m_ecsm; }
		inline PhysicsEngine2D& get_physic_engine() { return m_physics_engine; }
		inline EventDispatcher& get_event_dispatcher() { return m_dispatcher; }

	private:
		// Singleton
		static Application *s_application;
		
		bool m_running = true;
		float m_last_frame = 0.0f;
		std::unique_ptr<Window> m_window;
		Shader m_shader;
		Camera m_camera;
		ECSManager m_ecsm;
		PhysicsEngine2D m_physics_engine;
		
		EventDispatcher m_dispatcher;
		std::vector<graphics::Layer*> m_layers;
	};
}
