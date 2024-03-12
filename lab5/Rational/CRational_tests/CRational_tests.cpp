#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Rational/CRational.h"
#include <numeric>

void CheckRational(const CRational& rational, int numerator, int denominator)
{
	REQUIRE(rational.GetNumerator() == numerator);
	REQUIRE(rational.GetDenominator() == denominator);
}

void CheckOutput(const CRational& rational, const std::string& str)
{
	std::ostringstream out;
	out << rational;
	REQUIRE(out.str() == str);
}

TEST_CASE("Rational Initialization")
{
	CheckRational(CRational(4, 8), 1, 2);
	CheckRational(CRational(3, 9), 1, 3);
	CheckRational(CRational(1, -2), -1, 2);
	CheckRational(CRational(5, 2), 5, 2);
	CheckRational(CRational(-5, 2), -5, 2);
	CheckRational(CRational(5, -2), -5, 2);
	CheckRational(CRational(-5, -2), 5, 2);
	CheckRational(CRational(0), 0, 1);
	REQUIRE_THROWS_AS(CRational(1, 0), std::invalid_argument);
}
TEST_CASE("Comparison operators") //  и для чего нужен range
{
	SECTION("Opeartor ==")
	{

		REQUIRE(CRational(1, 2) == CRational(1, 2));
		REQUIRE(CRational(1, 3) == CRational(2, 6));
		REQUIRE(CRational(4, 1) == 4);
		REQUIRE(3 == CRational(3, 1));
		REQUIRE(!(CRational(1, 2) == CRational(2, 3)));
		REQUIRE(!(CRational(1, 2) == 7));
		REQUIRE(!(3 == CRational(2, 3)));
	}

	SECTION("Operator !=")
	{
		REQUIRE(!(CRational(1, 2) != CRational(1, 2)));
		REQUIRE(!(CRational(1, 3) != CRational(2, 6)));
		REQUIRE(!(CRational(4, 1) != 4));
		REQUIRE(!(3 != CRational(3, 1)));
		REQUIRE(CRational(1, 2) != CRational(2, 3));
		REQUIRE(CRational(1, 2) != 7);
		REQUIRE(3 != CRational(2, 3));
	}
	SECTION("Operator <")
	{
		REQUIRE(CRational(1, 2) < 7);
		REQUIRE(!(7 < CRational(1, 3)));
		REQUIRE(CRational(1, 2) < CRational(2, 3));
		REQUIRE(!(CRational(1, 2) < CRational(1, 4)));
	}
	SECTION("Operator <=")
	{
		REQUIRE(!(CRational(1, 2) <= CRational(1, 3)));
		REQUIRE(3 <= CRational(7, 2));
		REQUIRE(CRational(1, 4) <= CRational(1, 2));
		REQUIRE(CRational(6, 2) <= 3);
	}
	SECTION("Operator >")
	{
		REQUIRE(CRational(3, 1) > 2);
		REQUIRE(!(CRational(1, 2) > 7));
		REQUIRE(CRational(1, 2) > CRational(1, 4));
		REQUIRE(!(CRational(1, 4) > CRational(2, 3)));
	}
	SECTION("Operator >-")
	{
		REQUIRE(CRational(1, 2) >= CRational(1, 3));
		REQUIRE(!(3 >= CRational(8, 2)));
		REQUIRE(!(CRational(1, 4) >= CRational(1, 3)));
		REQUIRE(CRational(8, 4) >= 2);
	}
}

TEST_CASE("Assigment operator")
{
	//добавить +,-
	CheckRational(CRational(1, 2) += CRational(1, 2), 1, 1);
	CheckRational(CRational(1, 2) += 2, 5, 2);

	CheckRational(CRational(1, 2) -= CRational(1, 2), 0, 1);
	CheckRational(CRational(1, 2) -= 2, -3, 2);

	CheckRational(CRational(1, 2) *= CRational(2, 3), 1, 3);
	CheckRational(CRational(1, 2) *= 3, 3, 2);

	CheckRational(CRational(1, 2) /= CRational(2, 3), 3, 4);
	CheckRational(CRational(3, 4) /= CRational(3, 8), 2, 1);
	CheckRational(CRational(1, 2) /= 3, 1, 6);
	REQUIRE_THROWS_AS(CRational(2, 3) /= 0, std::invalid_argument);
}

TEST_CASE("Action operators")
{
	SECTION("Unary")
	{
		CheckRational(+CRational(3, 5), 3, 5);
		CheckRational(+CRational(-3, 5), -3, 5);

		CheckRational(-CRational(3, 5), -3, 5);
		CheckRational(-CRational(-3, 5), 3, 5);
	}
	SECTION("Binary")
	{
		CheckRational(CRational(1, 2) + CRational(1, 6), 2, 3);
		CheckRational(CRational(1, 2) + 1, 3, 2);
		CheckRational(1 + CRational(1, 2), 3, 2);

		CheckRational(CRational(1, 2) - CRational(1, 6), 1, 3);
		CheckRational(CRational(1, 2) - 1, -1, 2);
		CheckRational(1 - CRational(1, 2), 1, 2);
	}
}

TEST_CASE("Stream operators")
{
	SECTION("ostream")
	{
		CheckOutput(CRational(1, 2), "1/2");
		CheckOutput(CRational(0), "0/1");
		CheckOutput(CRational(1), "1/1");
		CheckOutput(CRational(21, 21), "1/1");
		CheckOutput(CRational(3, 9), "1/3");
	}
	SECTION("isteam")
	{
		{
			std::istringstream input("7/15");
			CRational r;
			input >> r;
			CheckRational(r, 7, 15);
		}
		{
			std::istringstream input("7.15");
			CRational r;
			input >> r;
			REQUIRE(!input);
		}
	}
}

TEST_CASE("Compound Fraction")
{
	{
		CRational r(9, 4);
		std::pair<int, CRational> compoundRational = r.ToCompoundFraction();
		REQUIRE(compoundRational.first == 2);
		CheckRational(compoundRational.second, 1, 4);
	}
	{
		CRational r(-8, 3);
		std::pair<int, CRational> compoundRational = r.ToCompoundFraction();
		REQUIRE(compoundRational.first == -2);
		CheckRational(compoundRational.second, -2, 3);
	}
	{
		CRational r(5, 6);
		std::pair<int, CRational> compoundRational = r.ToCompoundFraction();
		REQUIRE(compoundRational.first == 0);
		CheckRational(compoundRational.second, 5, 6);
	}
}

TEST_CASE("ABC")
{
	CRational r{ 0, 8 };
	CheckRational(r, 0, 1);
}