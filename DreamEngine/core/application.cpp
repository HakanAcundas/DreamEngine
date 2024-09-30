#include "application.h"

using namespace dream::graphics;
namespace dream 
{
	Application* Application::s_Application = nullptr;

	Application::Application()
	{
		s_Application = this;
		m_Window = std::make_shared<Window>();
		Renderer2D::GetSingleton()->Init();
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
		// TODO
		//Renderer2D::GetSingleton()->ShutDown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		auto it = std::find_if(m_Layers.begin(), m_Layers.end(), 
			[layer](const std::shared_ptr<Layer>& ptr) {
				return ptr.get() == layer;
			});
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

	void Application::OnEvent(Event& e)
	{
		std::cout << "We have an Event!! || " << e.ToString() << "\n";
		for (auto layer : m_Layers)
		{
			layer->OnEvent(e);
			if (e.handled)
				break;
		}
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Application::OnKeyPressed, this, std::placeholders::_1));
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		switch (e.GetKeyCode())
		{
		case 256:
			m_Running = false;
		}

		return false;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->Clear();
			for (auto layer : m_Layers)
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
	}
}