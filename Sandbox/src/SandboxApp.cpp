#include <Sheff.h>

class Sandbox : public Sheff::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Sheff::Application* Sheff::CreateApplication()
{
	return new Sandbox();
}