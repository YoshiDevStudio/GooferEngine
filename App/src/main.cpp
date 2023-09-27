#include "Goofer.h"

class App : public Goofer::Application
{
public:
	App()
	{

	}
	~App()
	{

	}
};


Goofer::Application* Goofer::CreateApplication()
{
	return new App();
}