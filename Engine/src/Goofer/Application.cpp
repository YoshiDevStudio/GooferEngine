#include "Application.h"
#include "Test.h"
#include "Delegate.h"
#include <iostream>
namespace Goofer
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		Test* test = new Test();
		void(Test:: * pFunctionA)() = &Test::Print;
		auto del1 = new Delegate<Test, void>(test, pFunctionA);
		
		del1->Invoke();
		while (true)
		{
			
		}
	}
}
