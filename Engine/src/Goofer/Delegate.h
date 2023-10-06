#pragma once
#include <functional>
#include <any>
namespace Goofer
{
	template <class classType, class returnType> class Delegate
	{
	public:
		
		Delegate(classType* clss, returnType(classType::* func)())
		{
			funcClass = clss;
			pFunction0Arg = func;
		}
		~Delegate() = default;

		/*void CreateDelegate(returnType(classType::* func)())
		{
			pFunction0Arg = func;
		}

		/*template <typename returnType, typename arg1>
		void CreateDelegate(returnType(*func)(arg1))
		{
			pFunction1Arg = func;
		}

		template <typename returnType, typename arg1, typename arg2>
		void CreateDelegate(returnType(*func)(arg1, arg2))
		{
			pFunction2Arg = func;
		}*/

		void Invoke()
		{
			if (pFunction0Arg == nullptr)
				return;

			std::cout << "Invoking" << std::endl;

			(*funcClass.*pFunction0Arg)();
		}
		/*template <typename arg1>
		void Invoke(arg1 par1)
		{

		}
		template <typename arg1, typename arg2>
		void Invoke(arg1 par1, arg2 par2)
		{

		}*/
	private:

		classType* funcClass;

		returnType(classType::*pFunction0Arg)();

		/*template <typename returnType, typename arg1>
		returnType(*pFunction1Arg)(arg1);

		template <typename returnType, typename arg1, typename arg2>
		returnType(*pFunction2Arg)(arg1, arg2);


		/*std::function<returnType(classType&)> pFunction0Arg;
		std::function<returnType(classType&, arg1)> pFunction1Arg;
		std::function<returnType(classType&, arg1, arg2)> pFunction2Arg;*/
	};
}

