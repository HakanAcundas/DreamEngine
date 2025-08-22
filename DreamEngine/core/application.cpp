#include "application.h"

using namespace dream::graphics;
namespace dream 
{
	Application *Application::s_application = nullptr;

	Application::Application()
	{
		s_application = this;
		m_window = std::make_shared<Window>();
		Renderer2D::get_instance()->init();
	}

	Application::~Application()
	{
		// TODO
		//Renderer2D::get_instance()->ShutDown();
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

	bool Application::on_key_pressed()
	{
		// switch (e.get_keycode())
		// {
		// case 256:
		// 	m_running = false;
		// }

		return false;
	}

	void Application::run()
	{
		while (m_running)
		{
			m_window->clear();
			dream::Input::update();
			dream::InputManager::get().update();
			for (auto layer : m_layers)
				layer->on_update();
			m_window->on_update();
		}
	}
}