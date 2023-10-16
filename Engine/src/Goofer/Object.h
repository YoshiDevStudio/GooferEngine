#pragma once
#include <iostream>
class Object
{
public:
	//This is just for testing purposes
	virtual void Print(int num1)
	{
		std::cout << "Print Virtual" << std::endl;
	}
};

