#include "shpch.h"
#include "Application.h"


#include "Sheff/Log.h"

#include <GLFW/glfw3.h>

namespace Sheff {

// TODO how does bind work? what does placeholders mean?
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		// TODO verify: unique ptr seems to do the deletion automatically when application shuts down
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); 
		// TODO 
	}
	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		
		SH_CORE_TRACE("{0}", e);
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		SH_TRACE(e);

		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}