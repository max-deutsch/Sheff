#pragma once

#ifdef SH_PLATFORM_WINDOWS
	
extern Sheff::Application* Sheff::CreateApplication();

int main(int argc, char** argv)
{	
	Sheff::Log::Init(); // TODO why is it necessary to put #include Log into Sheff.h to be able to use here? How are those connected?
	SH_CORE_WARN("Initialized Log!");
	int a = 5;
	SH_INFO("Client Log initialized! Var={0}", a);
	
	auto app = Sheff::CreateApplication();
	app->Run();
	delete app;
}
#endif