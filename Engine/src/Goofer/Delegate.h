#pragma once
#include <vector>
#include <iostream>
#include <any>
namespace Goofer
{
	template <typename returnType, typename... args>
	class DelegateBase
	{
	public:
		virtual returnType Invoke(args... parameters) = 0;
	};

	//if classType is base class with a virtual function and clss is a derived class that has overriden the virtual function it will call the overriden function
	template <typename classType, typename returnType, typename... args> class Delegate : public DelegateBase<returnType, args...>
	{
	public:
		
		Delegate(classType* clss, returnType(classType::* func)(args...), const char* name = nullptr)
		{
			funcClass = clss;
			pFunction = func;
			baseTypeName = name;
		}
		~Delegate() = default;

		returnType Invoke(args... parameters) override
		{
			if (pFunction == nullptr)
				return;

			(*funcClass.*pFunction)(parameters...);
		}

		const char* baseTypeName;
	private:
		classType* funcClass;
		returnType(classType::*pFunction)(args...);
	};

	//Can only hold delegates if they have same returnType and args...
	template <typename returnType, typename... args> class MulticastDelegate
	{
	public:
		MulticastDelegate()
		{

		}
		~MulticastDelegate()
		{
			pFunctions.clear();
		}

		//Adds function pointer to List
		template<typename classType>
		void AddDelegate(classType* clss, returnType(classType::* func)(args...))
		{
			auto del = new Delegate<classType, returnType, args...>(clss, func);
			auto baseDel = new Delegate<DelegateBase<returnType, args...>, returnType, args...>(del, &DelegateBase<returnType, args...>::Invoke, typeid(clss).name());

			classesPtr.push_back(clss);
			pFunctions.push_back(*baseDel);
		}

		template<typename classType>
		void RemoveDelegate(classType* clss, returnType(classType::* func)(args...))
		{
			for (int i = 0; i < pFunctions.size(); i++)
			{
				if (typeid(clss).name() == pFunctions[i].baseTypeName)
				{
					if (clss == std::any_cast<classType*>(classesPtr[i]))
					{
						pFunctions.erase(pFunctions.begin() + i);
						return;
					}
				}
				
			}
		}

		void Invoke(args... parameters)
		{
			for (int i = 0; i < pFunctions.size(); i++)
			{
				pFunctions[i].Invoke(parameters...);
			}
		}
	private:
		std::vector<std::any> classesPtr;
		std::vector<Delegate<DelegateBase<returnType, args...>, returnType, args...>> pFunctions;
	};
}

