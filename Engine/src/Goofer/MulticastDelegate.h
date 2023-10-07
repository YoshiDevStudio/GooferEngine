#pragma once
#include <vector>
namespace Goofer
{
	template <typename classType, typename returnType, typename... args> class MulticastDelegate
	{
	public:
		MulticastDelegate()
		{

		}
		~MulticastDelegate() = default;


		void AddDelegate(classType* clss, returnType(classType::* func)(args...))
		{
			funcClasses.push_back(clss);
			pFunctions.push_back(func);
		}

		void Invoke(args... parameters)
		{
			std::cout << "Invoking" << std::endl;

			for (int i = 0; i < pFunctions.size(); i++)
			{
				if (funcClasses[i] != nullptr && pFunctions[i] != nullptr)
				{
					(*funcClasses[i].*pFunctions[i])(parameters...);
				}
			}
		}

	private:

		std::vector<classType*> funcClasses;

		std::vector<returnType(classType::*)(args...)> pFunctions;
	};
}

