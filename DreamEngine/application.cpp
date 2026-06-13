#include "application.hpp"

using namespace dream::graphics;
namespace dream 
{
	Application *Application::s_application = nullptr;

	Application::Application()
	{
		s_application = this;
		m_window = std::make_unique<Window>();
		m_window->set_event_callback([this](Event& e)
		{
			this->on_event(e);
		});

		m_ecm = ECManager();
		m_dispatcher = EventDispatcher();
		
		m_ecm.init();
		m_physics_engine = PhysicsEngine2D(m_ecm);
		Renderer2D::get_instance()->init();
	}

	Application::~Application()
	{
		delete s_application;
	}

	void Application::push_layer(Layer *layer)
	{
		m_layers.emplace_back(layer);
	}

	void Application::pop_layer(Layer *layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
			m_layers.erase(it);
	}

	void Application::on_event(Event& event)
	{
		m_dispatcher.post(event);
	}

	bool Application::on_key_pressed()
	{
		return false;
	}

	void Application::run()
	{
		while (!glfwWindowShouldClose(m_window->get_glfw_window()))
		{
			m_window->clear();
			for (auto layer : m_layers)
				layer->on_update();
			m_window->on_update();
		}
	}
}