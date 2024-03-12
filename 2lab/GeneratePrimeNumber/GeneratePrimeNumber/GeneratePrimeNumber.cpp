#include "GeneratePrimeNumber_handler.h"
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

int ValidationArguments(int argc)
{
	if (argc != 2)
	{
		std::cout << "Error, please enter: GeneratePrimeNumber.exe <number>" << std::endl;
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	int result = ValidationArguments(argc);
	if (result == 1)
		return 1;
	int upperBound = atoi(argv[1]);
	std::set<int> primes = GeneratePrimeNumbersSet(upperBound);
	PrintPrimeNumbers(primes, std::cout);
	return 0;
}
