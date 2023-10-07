#include "Application.h"
#include "Test.h"
#include "Delegate.h"
#include "MulticastDelegate.h"
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
		Test* test1 = new Test();
		test1->numToAdd = 13;
		Test* test2 = new Test();
		test2->numToAdd = 7;

		auto multiDel = new MulticastDelegate<Test, void, int>();
		multiDel->AddDelegate(test1, &Test::Print);
		multiDel->AddDelegate(test2, &Test::Print);

		multiDel->Invoke(5);

		//auto del1 = new Delegate<Test, void, int>(test, &Test::Print);
		//del1->Invoke(8);
		while (true)
		{
			
		}
	}
}
