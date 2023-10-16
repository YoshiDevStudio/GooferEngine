#pragma once
#include <vector>
#include <iostream>
#include "Object.h"
namespace Goofer
{
	template <typename classType, typename returnType, typename... args> class Delegate : public Object
	{
	public:
		
		Delegate(classType* clss, returnType(classType::* func)(args...))
		{
			funcClass = clss;
			pFunction = func;
		}
		~Delegate() = default;

		void Invoke(args... parameters)
		{
			if (pFunction == nullptr)
				return;

			std::cout << "Invoking" << std::endl;

			(*funcClass.*pFunction)(parameters...);
		}

	private:
		classType* funcClass;
		returnType(classType::*pFunction)(args...);
	};

	template <typename classType, typename returnType, typename... args> class MulticastDelegate : public Object
	{
	public:
		MulticastDelegate()
		{

		}
		~MulticastDelegate() = default;

		void AddDelegate(classType* clss, returnType(classType::* func)(args...))
		{
			funcClasses.push_back(clss);
			delegates.push_back(func);

		}

		void Invoke(args... parameters)
		{
			std::cout << "Invoking" << std::endl;

			for (int i = 0; i < delegates.size(); i++)
			{
				(funcClasses[i]->*delegates[i])(parameters...);
			}
		}
	private:

		std::vector<classType*> funcClasses;

		std::vector<returnType(classType::*)(args...)> delegates;
	};
}

