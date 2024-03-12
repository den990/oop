#include "../Calculator/Function.h"
#include "../../../catch/catch.hpp"

TEST_CASE("function Interpret")
{
	SECTION("Valid Numbers")
	{

		Function func;
		double firstNumber = 4.00, secondNumber = 5.00;
		Function::Operation operation = Function::Operation::MUL;
		REQUIRE(func.CalculateValue(firstNumber, secondNumber, operation) == 20);
		operation = Function::Operation::DIV;
		REQUIRE(func.CalculateValue(firstNumber, secondNumber, operation) == 1.25);
		operation = Function::Operation::ADD;
		REQUIRE(func.CalculateValue(firstNumber, secondNumber, operation) == 9);
		operation = Function::Operation::SUB;
		REQUIRE(func.CalculateValue(firstNumber, secondNumber, operation) == -1);
	}
}