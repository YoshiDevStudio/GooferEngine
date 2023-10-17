#include "Application.h"
#include "Test.h"
#include "Delegate.h"
#include <iostream>
#include "Object.h"
#include "Array.h"
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
		test1->numToAdd = 0;
		Test* test2 = new Test();
		test2->numToAdd = 1;

		/*auto multiDel = new MulticastDelegate<Test, void, int>();
		multiDel->AddDelegate(test1, &Object::Print);
		multiDel->AddDelegate(test2, &Object::Print);

		//multiDel->RemoveDelegate(test1, &Object::Print);

		multiDel->Invoke(5);*/
		
		//auto del1 = new Delegate<Test, void, int>(test1, &Test::Print);
		//del1->Invoke(8);
		while (true)
		{
			
		}
	}
}
