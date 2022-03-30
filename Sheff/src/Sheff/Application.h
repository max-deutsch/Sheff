#pragma once

#include "Core.h"
#include "Window.h"
#include "Sheff/LayerStack.h"
#include "Sheff/Events/Event.h"
#include "Sheff/Events/ApplicationEvent.h"




namespace Sheff {

	/*
	* Base Class for a client application.
	* On creation handles setting up a window
	*/
	class SHEFF_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;

	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
