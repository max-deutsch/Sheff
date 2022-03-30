#include <Sheff.h>

class ExampleLayer : public Sheff::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override // TODO what if override is not specified?
	{
		SH_INFO("ExampleLAyer::Update");
	}

	void OnEvent(Sheff::Event& event) override
	{
		SH_TRACE("{0}", event);
	}
};

class Sandbox : public Sheff::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Sheff::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Sheff::Application* Sheff::CreateApplication()
{
	return new Sandbox();
}