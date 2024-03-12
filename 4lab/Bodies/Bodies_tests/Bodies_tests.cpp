#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Bodies/CBody.h"
#include "../Bodies/CBodyController.h"
#include "../Bodies/CCompound.h"
#include "../Bodies/CCone.h"
#include "../Bodies/CCylinder.h"
#include "../Bodies/CParallelepiped.h"
#include "../Bodies/CSolidBody.h"
#include "../Bodies/CSphere.h"
#include "../Bodies/Result.h"
#include <sstream>

TEST_CASE("Add Body")
{
	std::ostringstream output;
	SECTION("Add Sphere")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n1\n20 40");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::OK);
		REQUIRE(bodies.size() == 1);
	}
	SECTION("Add Parallelepiped")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n2\n20 30 40 50");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::OK);
		REQUIRE(bodies.size() == 1);
	}
	SECTION("Add Cone")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n3\n20 30 40");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::OK);
		REQUIRE(bodies.size() == 1);
	}
	SECTION("Add Cylinder")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n4\n20 30 40");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::OK);
		REQUIRE(bodies.size() == 1);
	}
	SECTION("Add Compound Body")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n5\n3\n20 30 40\n1\n20 40");
		CBodyController cbody(input, output, bodies);
		while (input)
		{
			cbody.Interpret();
		}
		REQUIRE(bodies.size() == 1);
	}
}
TEST_CASE("Enter add body and exit")
{
	std::ostringstream output;
	SECTION("Simple Body")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n5");
		CBodyController cbody(input, output, bodies);
		while (!input.eof())
		{
			REQUIRE(cbody.Interpret().status != Status::ERROR_);
		}
		REQUIRE(bodies.size() == 0);
	}
	SECTION("Compound Body")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("5\n5");
		CBodyController cbody(input, output, bodies);
		while (!input.eof())
		{
			REQUIRE(cbody.Interpret().status != Status::ERROR_);
		}
		REQUIRE(bodies.size() == 0);
	}
}

TEST_CASE("Not exist command")
{
	std::ostringstream output;
	SECTION("Empty command")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::ERROR_);
		REQUIRE(bodies.size() == 0);
	}
	SECTION("Not exist command")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("jsasj");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status:: ERROR_);
		REQUIRE(output.str() == "Команды:\n1 - Добавить тело\n2 - Найти тело с наибольшей массой\n3 - Найти тело которое будет легче всего весить в воде\n4 - Вывести информацию обо всех телах\n5 - Выйти из программы\n");
		REQUIRE(bodies.size() == 0);
	}
}

TEST_CASE("Cyclic body insertion")
{
	auto b1 = std::make_shared<CCompound>();
	auto b2 = std::make_shared<CCompound>();
	auto b3 = std::make_shared<CCompound>();
	b1->AddChild(b2);
	b2->AddChild(b3);
	REQUIRE(!b3->AddChild(b1));
	REQUIRE(!b2->AddChild(b2));

}
