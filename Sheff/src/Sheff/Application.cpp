#include "shpch.h"
#include "Application.h"

#include "Sheff/Events/ApplicationEvent.h"
#include "Sheff/Log.h"

namespace Sheff {
	Application::Application()
	{

	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		SH_TRACE(e);

		while (true);
	}
}