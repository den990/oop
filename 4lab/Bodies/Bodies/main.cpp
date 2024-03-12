#include <iostream>
#include "CBodyController.h"
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::vector<std::shared_ptr<CBody>> bodies;
	CBodyController cbody(std::cin, std::cout, bodies);
	Result result;
	while (!std::cin.eof())
	{
		std::cin.seekg(0);
		result = cbody.Interpret();
		if (result.status == Status::EXIT)
		{
			return 0;
		}
		if (result.status == Status::ERROR_)
		{
			std::cout << result.errorMessage << std::endl;
		}
	}
}

