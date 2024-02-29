#include "Application.h"

using namespace dream::graphics;

namespace dream 
{

	Application* Application::s_Application = nullptr;

	Application::Application()
	{
		s_Application = this;
		m_Window = new Window();
		// TODO Window event system
		Renderer2D::GetSingleton()->Init();
	}

	Application::~Application()
	{
		//Renderer2D::GetSingleton()->ShutDown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
	}

	void Application::OnEvent()
	{
		// TODO
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->Clear();
			for (Layer* layer : m_Layers)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}
}