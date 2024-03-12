#include "../Calculator/ExpressionParse.h"
#include "../../../catch/catch.hpp"
#include <iostream>

TEST_CASE("Parsing invalid command")
{
	ExpressionParse parser;
	ExpressionParse::ExpressionData expr;
	std::string inputString = "hello b=5";
	
	REQUIRE(parser.ParseCommand(inputString, expr).status == Status::ERROR);
	inputString = "var 34g8";
	REQUIRE(parser.ParseCommand(inputString, expr).status == Status::ERROR);
	inputString = "let 40gk=erg";
	REQUIRE(parser.ParseCommand(inputString, expr).status == Status::ERROR);
	inputString = "printvarsdr";
	REQUIRE(parser.ParseCommand(inputString, expr).status == Status::ERROR);
}

TEST_CASE("Parsing print commands")
{
	ExpressionParse parser;
	ExpressionParse::ExpressionData expr;
	std::string inputString;
	SECTION("ParseCommand 'print'")
	{
		inputString = "print ab";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::OK);
		REQUIRE(expr.command == ExpressionParse::Command::PRINTVALUE);
		REQUIRE(expr.identifiers[0] == "ab");
		inputString = "print";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::ERROR);
		inputString = "print 983";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::ERROR);
	}

	SECTION("ParseCommand 'printvars'")
	{
		inputString = "printvars";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::OK);
		REQUIRE(expr.command == ExpressionParse::Command::PRINTALLVARIABLES);
		REQUIRE(expr.identifiers.empty());
	}

	SECTION("ParseCommand 'printfns'")
	{
		inputString = "printfns";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::OK);
		REQUIRE(expr.command == ExpressionParse::Command::PRINTALLFUNCTIONS);
		REQUIRE(expr.identifiers.empty());
	}
}

TEST_CASE("Parsing variable commands")
{
	ExpressionParse parser;
	ExpressionParse::ExpressionData expr;
	std::string inputString;
	SECTION("ParseCommand 'var'")
	{
		inputString = "var abc";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::OK);

		REQUIRE(expr.command == ExpressionParse::Command::DECLAREVARIABLE);
		REQUIRE(expr.identifiers.size() == 1);
		REQUIRE(expr.identifiers[0] == "abc");
		inputString = "var 9834gh";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::ERROR);
	}

	SECTION("ParseCommand 'let'")
	{
		inputString = "let b=6";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::OK);

		REQUIRE(expr.command == ExpressionParse::Command::ASSIGNVARIABLE);
		REQUIRE(expr.identifiers.size() == 1);
		REQUIRE(expr.identifiers[0] == "b");
		REQUIRE(expr.value == 6);
		inputString = "let another_variable=b";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::OK);

		REQUIRE(expr.command == ExpressionParse::Command::ASSIGNVARIABLE);
		REQUIRE(expr.identifiers.size() == 2);
		REQUIRE(expr.identifiers[0] == "another_variable");
		REQUIRE(expr.identifiers[1] == "b");
		inputString = "let +#t=4";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::ERROR);
	}
}

TEST_CASE("Parsing function commands")
{
	ExpressionParse parser;
	ExpressionParse::ExpressionData expr;
	std::string inputString;
	SECTION("ParseCommand function with two parameters")
	{
		inputString = "fn product_of_x_and_y=x*y";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::OK);

		REQUIRE(expr.command == ExpressionParse::Command::DECLAREVARIABLE);
		REQUIRE(expr.identifiers.size() == 3);
		REQUIRE(expr.identifiers[0] == "product_of_x_and_y");
		REQUIRE(expr.identifiers[1] == "x");
		REQUIRE(expr.identifiers[2] == "y");
		REQUIRE(expr.operation == '*');
	}

	SECTION("ParseCommand function with one parameter")
	{
		inputString = "fn alias_for_x=x";
		REQUIRE(parser.ParseCommand(inputString, expr).status == Status::OK);

		REQUIRE(expr.command == ExpressionParse::Command::DECLAREVARIABLE);
		REQUIRE(expr.identifiers.size() == 2);
		REQUIRE(expr.identifiers[0] == "alias_for_x");
		REQUIRE(expr.identifiers[1] == "x");
	}
}