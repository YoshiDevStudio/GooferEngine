#pragma once
#include <iostream>
namespace Goofer
{
	class Test
	{
	public:
		Test()
		{

		}
		~Test() = default;

		void Print()
		{
			std::cout << "print no args" << std::endl;
		}

		void Print(int num1)
		{
			std::cout << "print one args: " << num1 + numToAdd << std::endl;
		}

		void Print(int num1, int num2)
		{
			std::cout << "print two args: " << num1 << " and " << num2 << std::endl;
		}

		int numToAdd = 0;
	};
}