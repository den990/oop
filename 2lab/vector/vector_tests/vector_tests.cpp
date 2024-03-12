#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../vector/Proccess.h"
#include <iostream>
#include <sstream>

TEST_CASE("ReadVector function")
{
	SECTION("Reading empty vector")
	{
		std::vector<double> numbers;
		std::vector<double> emptyVector;
		std::istringstream input;
		ReadVector(numbers, input);
		REQUIRE(numbers == emptyVector);
		REQUIRE(numbers.empty());
	}
	SECTION("Reading vector with 1 element")
	{
		std::vector<double> numbers;
		std::istringstream input("5.02020");
		ReadVector(numbers, input);
		REQUIRE(numbers.size() == 1);
		REQUIRE(numbers[0] == 5.02020);
	}
	SECTION("Reading vector with more elements")
	{
		std::vector<double> numbers;
		std::istringstream input("0 2 4 6 8 10");
		ReadVector(numbers, input);
		REQUIRE(numbers == std::vector<double>{ 0, 2, 4, 6, 8, 10 });
		REQUIRE(numbers.size() == 6);
	}
}

TEST_CASE("VectorOperation function")
{
	SECTION("VectorOperation empty")
	{
		std::vector<double> numbers;
		std::vector<double> emptyVector;
		VectorOperation(numbers);
		REQUIRE(numbers == emptyVector);
		REQUIRE(numbers.size() == 0);
	}
	SECTION("VectorOperation with 1 element")
	{
		std::vector<double> numbers = { 5 };
		std::vector<double> resultVector = { 2 };
		VectorOperation(numbers);
		REQUIRE(numbers == resultVector);
	}
	SECTION("VectorOperation with more elements")
	{
		std::vector<double> numbers = { 0, 2, 4, 6, 8, 10 };
		std::vector<double> resultVector = { 0, 0.4, 0.8, 1.2, 1.6, 2 };
		VectorOperation(numbers);
		REQUIRE(numbers == resultVector);
	}
}