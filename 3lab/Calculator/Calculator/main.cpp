#include <iostream>
#include "Calculator.h"

int main()
{
	ExpressionParse express;
	Calculator calc(express, std::cin, std::cout);
	while (!std::cin.eof())
	{
		calc.Interpret();
	}

	return 0;
}