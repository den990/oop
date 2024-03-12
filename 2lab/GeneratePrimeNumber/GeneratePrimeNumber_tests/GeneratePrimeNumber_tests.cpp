#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../GeneratePrimeNumber/GeneratePrimeNumber_handler.h"

TEST_CASE("GeneratePrimeNumbersSet function")
{
	SECTION("Not correct set for upper bound")
	{
		std::set<int> expected;
		REQUIRE(GeneratePrimeNumbersSet(0) == expected);
	}
	SECTION("Correct set for upper bound")
	{
		std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
		REQUIRE(GeneratePrimeNumbersSet(100) == expected);
		expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };
		REQUIRE(GeneratePrimeNumbersSet(50) == expected);
	}
	#ifdef NDEBUG
	SECTION("Max upper bound")
	{
		REQUIRE(GeneratePrimeNumbersSet(100000000).size() == 5761455);
	}
	#endif // !1


}

TEST_CASE("PrintPrimeNumbers function")
{
	SECTION("Print empty set")
	{
		std::ostringstream output;
		std::set<int> expected;
		PrintPrimeNumbers(expected, output);
		REQUIRE(output.str() == "\n");
	}
	SECTION("Print set of 1 element")
	{
		std::ostringstream output;
		std::set<int> expected = { 2 };
		PrintPrimeNumbers(expected, output);
		REQUIRE(output.str() == "2, \n");
	}
	SECTION("Print set of many elements")
	{
		std::ostringstream output;
		std::set<int> expected = { 2, 3, 5, 7 };
		PrintPrimeNumbers(expected, output);
		REQUIRE(output.str() == "2, 3, 5, 7, \n");
	}
}