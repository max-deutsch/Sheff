#pragma once

#include "Core.h"

namespace Sheff {

	class SHEFF_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
