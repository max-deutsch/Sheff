#pragma once

#ifdef SF_PLATFORM_WINDOWS
	
extern Sheff::Application* Sheff::CreateApplication();

int main(int argc, char** argv)
{	
	printf("Sheff Engine\n");
	auto app = Sheff::CreateApplication();
	app->Run();
	delete app;
}
#endif