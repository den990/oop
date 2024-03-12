#include <iostream>
#include "Car.h"
#include "WorkCommand.h"
int main()
{
	Car car;
	std::pair <WorkCommand::Status, bool> parseResult;
	WorkCommand WorkCommand(car, std::cin, std::cout);
	while ((parseResult = WorkCommand.Result()).first != WorkCommand::Status::EXIT)
	{
		if (parseResult.first == WorkCommand::Status::ERROR)
		{
			std::cout << "This command does not exist." << std::endl;
		}
		if (parseResult.second == false)
		{
			std::cout << car.GetLastErrorMessage();
		}
	}
}