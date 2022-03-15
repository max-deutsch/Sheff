#include "shpch.h"
#include "Application.h"

#include "Sheff/Events/ApplicationEvent.h"
#include "Sheff/Log.h"

#include <GLFW/glfw3.h>

namespace Sheff {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		// TODO verify: unique ptr seems to do the deletion automatically when application shuts down
	}
	Application::~Application()
	{

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
}