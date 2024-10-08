#include "application.h"

using namespace dream::graphics;
namespace dream 
{
	Application *Application::s_application = nullptr;

	Application::Application()
	{
		s_application = this;
		m_window = std::make_shared<Window>();
		Renderer2D::get_singleton()->init();
		m_window->set_event_callback(std::bind(&Application::on_event, this, std::placeholders::_1));
	}

	Application::~Application()
	{
		// TODO
		//Renderer2D::get_singleton()->ShutDown();
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

	void Application::on_event(Event &e)
	{
		std::cout << "We have an Event!! || " << e.to_string() << "\n";
		for (auto layer : m_layers)
		{
			layer->on_event(e);
			if (e.handled)
				break;
		}

		switch (e.get_event_type())
		{
		case Event::EventType::KEY_PRESSED:
			on_key_pressed(static_cast<KeyPressedEvent&>(e));
			break;
		}

	}

	bool Application::on_key_pressed(KeyPressedEvent &e)
	{
		switch (e.get_keycode())
		{
		case 256:
			m_running = false;
		}

		return false;
	}

	void Application::run()
	{
		while (m_running)
		{
			m_window->clear();
			for (auto layer : m_layers)
				layer->on_update();
			m_window->on_update();
		}
	}
}