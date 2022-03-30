#include "shpch.h"
#include "Application.h"


#include "Sheff/Log.h"

#include <glad/glad.h>

namespace Sheff {

// TODO how does bind work? what does placeholders mean?
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	// Holding a singleton to our application that can be accessed everywhere
	// TODO why is it sett to a nullptr here?
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SH_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		// TODO verify: unique ptr seems to do the deletion automatically when application shuts down
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); 
	}
	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));		

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		SH_TRACE(e);

		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}