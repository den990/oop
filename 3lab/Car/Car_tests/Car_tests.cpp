#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Car/Car.h"
//showtestcaverage
TEST_CASE("Check Initialisation")
{
	Car car;
	SECTION("Check parameters")
	{
		REQUIRE(car.GetDirection() == Car::Direction::IMMOBILE);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(!car.IsTurnedOn());
		REQUIRE(car.GetSpeed() == 0);
	}
	SECTION("Check engine")
	{
		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.IsTurnedOn());
		REQUIRE(car.TurnOffEngine());
		REQUIRE(!car.IsTurnedOn());
	}
}

TEST_CASE("SetGear function")
{
	Car car;
	SECTION("Set Gear with turned off engine")
	{
		REQUIRE(!car.SetGear(1));
		REQUIRE(!car.SetGear(-1));
		REQUIRE(!car.SetGear(2));
	}
	car.TurnOnEngine();
	SECTION("Set Gear 1, -1 from 0 with turned on engine")
	{
		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetGear() == 1);
		REQUIRE(car.SetGear(-1));
		REQUIRE(car.GetGear() == -1);
	}
	SECTION("Set incorrect gear from 0")
	{
		REQUIRE(!car.SetGear(2));
		REQUIRE(car.GetGear() == 0);
		REQUIRE(!car.SetGear(3));
		REQUIRE(car.GetGear() == 0);
		REQUIRE(!car.SetGear(4));
		REQUIRE(car.GetGear() == 0);
		REQUIRE(!car.SetGear(5));
		REQUIRE(car.GetGear() == 0);
		REQUIRE(!car.SetGear(10));
		REQUIRE(car.GetGear() == 0);
	}
	SECTION("Set Gear on possible from 1")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		REQUIRE(car.SetGear(0));
		car.SetGear(1);
		REQUIRE(car.SetGear(1));
		car.SetGear(1);
		REQUIRE(car.SetGear(2));
		car.SetGear(1);
		REQUIRE(!car.SetGear(3));
		REQUIRE(!car.SetGear(5));
		REQUIRE(!car.SetGear(-1));
	}
	SECTION("Set Geat on possible from -1")
	{
		car.SetGear(-1);
		REQUIRE(car.SetGear(0));
		car.SetGear(-1);
		REQUIRE(car.SetGear(-1));
		car.SetGear(-1);
		REQUIRE(car.SetGear(1));
	}
}

TEST_CASE("Set Speed function")
{
	Car car;
	car.TurnOnEngine();
	SECTION("Set Speed for every gear")
	{
		SECTION("0 gear")
		{
			REQUIRE(!car.SetSpeed(20));
		}
		SECTION("R gear")
		{
			car.SetGear(-1);
			REQUIRE(car.SetSpeed(0));
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.SetSpeed(20));
			REQUIRE(car.GetSpeed() == 20);
			REQUIRE(car.SetSpeed(10));
			REQUIRE(car.GetSpeed() == 10);
			REQUIRE(!car.SetSpeed(30));
			REQUIRE(car.GetSpeed() == 10);
		}
		SECTION("1 gear")
		{
			car.SetGear(1);
			REQUIRE(car.SetSpeed(0));
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(car.SetSpeed(20));
			REQUIRE(car.GetSpeed() == 20);
			REQUIRE(!car.SetSpeed(40));
			REQUIRE(car.GetSpeed() == 20);
		}
		SECTION("2 gear")
		{
			car.SetGear(1);
			REQUIRE(car.GetGear() == 1);
			REQUIRE(car.SetSpeed(20));
			REQUIRE(car.GetSpeed() == 20);
			car.SetGear(2);
			REQUIRE(car.GetGear() == 2);
			REQUIRE(car.SetSpeed(50));
			REQUIRE(car.GetSpeed() == 50);
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(!car.SetSpeed(60));
			REQUIRE(car.GetSpeed() == 30);
		}
		SECTION("3 gear")
		{
			car.SetGear(1);
			car.SetSpeed(30);
			car.SetGear(3);
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(car.SetSpeed(60));
			REQUIRE(car.GetSpeed() == 60);
			REQUIRE(car.SetSpeed(45));
			REQUIRE(car.GetSpeed() == 45);
			REQUIRE(!car.SetSpeed(80));
			REQUIRE(car.GetSpeed() == 45);
		}
		SECTION("4 gear")
		{
			car.SetGear(1);
			car.SetSpeed(30);
			car.SetGear(2);
			car.SetSpeed(40);
			car.SetGear(4);
			REQUIRE(car.SetSpeed(40));
			REQUIRE(car.GetSpeed() == 40);
			REQUIRE(car.SetSpeed(90));
			REQUIRE(car.GetSpeed() == 90);
			REQUIRE(car.SetSpeed(55));
			REQUIRE(car.GetSpeed() == 55);
			REQUIRE(!car.SetSpeed(100));
			REQUIRE(car.GetSpeed() == 55);
		}
		SECTION("1 gear")
		{
			car.SetGear(1);
			car.SetSpeed(30);
			car.SetGear(2);
			car.SetSpeed(50);
			car.SetGear(5);
			REQUIRE(car.SetSpeed(50));
			REQUIRE(car.SetSpeed(150));
			REQUIRE(car.SetSpeed(100));
			REQUIRE(!car.SetSpeed(160));
		}
	}
}

TEST_CASE("Exceptions with gears")
{
	Car car;
	car.TurnOnEngine();
	SECTION("Switch from -1 to 1")
	{
		car.SetGear(-1);
		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetGear() == 1);
		car.SetGear(-1);
		REQUIRE(car.GetGear() == -1);
		car.SetSpeed(10);
		REQUIRE(car.GetSpeed() == 10);
		REQUIRE(!car.SetGear(1));
		car.SetGear(0);
		REQUIRE(!car.SetGear(1));
	}
	SECTION("Set Gear -1 at speed")
	{
		car.SetGear(1);
		car.SetSpeed(10);
		REQUIRE(!car.SetGear(-1));
	}
}

TEST_CASE("Get parameters")
{
	SECTION("Get Speed")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		REQUIRE(car.GetSpeed() == 10);
		car.SetSpeed(20);
		REQUIRE(car.GetSpeed() == 20);
	}
	SECTION("Get Gear")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		REQUIRE(car.GetGear() == 1);
		car.SetGear(0);
		REQUIRE(car.GetGear() == 0);
		car.SetGear(-1);
		REQUIRE(car.GetGear() == -1);
	}
	SECTION("Get Direction")
	{
		Car car;
		car.TurnOnEngine();
		REQUIRE(car.GetDirection() == Car::Direction::IMMOBILE);
		car.SetGear(1);
		REQUIRE(car.GetDirection() == Car::Direction::IMMOBILE);
		car.SetSpeed(10);
		REQUIRE(car.GetDirection() == Car::Direction::FORWARD);
		car.SetSpeed(0);
		car.SetGear(-1);
		car.SetSpeed(10);
		REQUIRE(car.GetDirection() == Car::Direction::BACKWARD);
	}
}