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

			(*funcClass.*pFunction)(parameters...);
		}

	private:
		classType* funcClass;
		returnType(classType::*pFunction)(args...);
	};

	//Can only hold delegates if they have all same types
	//if classType is base class with a virtual function and clss is a derived class that has overriden the virtual function it will call the overriden function
	template <typename classType, typename returnType, typename... args> class MulticastDelegate : public Object
	{
	public:
		MulticastDelegate()
		{

		}
		~MulticastDelegate()
		{
			funcClasses.clear();
			pFunctions.clear();
			delete *funcClasses;
			delete *pFunctions;
		}

		//Adds function pointer to List
		void AddDelegate(classType* clss, returnType(classType::* func)(args...))
		{
			funcClasses.push_back(clss);
			pFunctions.push_back(func);
		}

		void RemoveDelegate(classType* clss, returnType(classType::* func)(args...))
		{
			for (int i = 0; i < pFunctions.size(); i++)
			{
				if (clss == funcClasses[i] || func == pFunctions[i])
				{
					funcClasses.erase(funcClasses.begin() + i);
					pFunctions.erase(pFunctions.begin() + i);
					return;
				}
			}
		}

		void Invoke(args... parameters)
		{
			for (int i = 0; i < pFunctions.size(); i++)
			{
				(funcClasses[i]->*pFunctions[i])(parameters...);
			}
		}
	private:

		std::vector<classType*> funcClasses;

		std::vector<returnType(classType::*)(args...)> pFunctions;
	};
}

