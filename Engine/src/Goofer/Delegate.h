#pragma once

namespace Goofer
{
	template <typename classType, typename returnType, typename... args> class Delegate
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
}

