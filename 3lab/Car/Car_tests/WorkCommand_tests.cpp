#include "../../../catch/catch.hpp"
#include "../Car/Car.h"
#include "../Car/WorkCommand.h"

TEST_CASE("fd")
{
	Car car;
	std::ostringstream output;
	SECTION("Unknown command")
	{
		std::istringstream input("dsjkks");
		WorkCommand WorkCommand(car, input, output);
		REQUIRE(WorkCommand.Result().first == WorkCommand::Status(2));
	}
	SECTION("Incorrect argument")
	{
		std::istringstream input("SetGear 10");
		WorkCommand WorkCommand(car, input, output);
		REQUIRE(WorkCommand.Result().second == false );
	}
	SECTION("Correct commands")
	{
		std::istringstream input("EngineOn\nSetGear -1\nSetSpeed 20\nSetGear 0\nSetSpeed 10\nSetSpeed 15\nSetGear 1\nEngineOff\nSetSpeed 0\nEngineOff\n");
		WorkCommand WorkCommand(car, input, output);
		// turn on engine
		REQUIRE(WorkCommand.Result().first == WorkCommand::Status(0));
		REQUIRE(car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetDirection() == Car::Direction::IMMOBILE);
		REQUIRE(WorkCommand.Result().first == WorkCommand::Status(0));
		REQUIRE(car.IsTurnedOn());
		REQUIRE(car.GetGear() == -1);
		REQUIRE(car.GetDirection() == Car::Direction::IMMOBILE);

		// accelerate to 20 moving backwards
		REQUIRE(WorkCommand.Result().first == WorkCommand::Status(0));
		REQUIRE(car.IsTurnedOn());
		REQUIRE(car.GetGear() == -1);
		REQUIRE(car.GetSpeed() == 20);
		REQUIRE(car.GetDirection() == Car::Direction::BACKWARD);

		// set neutral gear
		REQUIRE(WorkCommand.Result().first == WorkCommand::Status(0));
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 20);
		REQUIRE(car.GetDirection() == Car::Direction::BACKWARD);

		// brake to 10
		REQUIRE(WorkCommand.Result().first == WorkCommand::Status(0));
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 10);
		REQUIRE(car.GetDirection() == Car::Direction::BACKWARD);

		// trying to accelerate from 10 to 15 on neutral gear
		REQUIRE(WorkCommand.Result().second == false);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 10);
		REQUIRE(car.GetDirection() == Car::Direction::BACKWARD);

		// trying to set gear 1 while moving backwards on neutral gear
		REQUIRE(WorkCommand.Result().second == false);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 10);
		REQUIRE(car.GetDirection() == Car::Direction::BACKWARD);

		// trying turn off engine while moving backwards on neutral gear
		REQUIRE(WorkCommand.Result().second == false);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 10);
		REQUIRE(car.GetDirection() == Car::Direction::BACKWARD);

		// brake to 0
		REQUIRE(WorkCommand.Result().first == WorkCommand::Status(0));
		REQUIRE(car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == Car::Direction::IMMOBILE);

		// turn off engine
		REQUIRE(WorkCommand.Result().first == WorkCommand::Status(0));
		REQUIRE(!car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == Car::Direction::IMMOBILE);
	}
}
TEST_CASE("Empty string ignoring and 'Exit' command behavior")
{
	std::ostringstream output;
	Car car;

	SECTION("Empty string is valid meaning that there is nothing to execute")
	{
		std::istringstream input("\n");
		WorkCommand workCommand(car, input, output);

		REQUIRE(!car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == Car::Direction::IMMOBILE);

		REQUIRE(workCommand.Result().first == WorkCommand::Status(2));
	}

	SECTION("Exit command invokes 'Exit' status")
	{
		std::istringstream input("Exit\n");
		WorkCommand workCommand(car, input, output);

		REQUIRE(workCommand.Result().first == WorkCommand::Status(1));
	}
}

TEST_CASE("Testing 'Info' command correct behavior")
{
	std::ostringstream output;
	Car car;

	SECTION("Info command prints info into ostream")
	{
		std::istringstream input("Info\n");
		WorkCommand workCommand(car, input, output);

		REQUIRE(workCommand.Result().first == WorkCommand::Status(0));

		REQUIRE(output.str() == "Engine: Off\nDirection: Immobile\nGear: N\nSpeed: 0\n");
	}

	SECTION("Print info after changing car's state")
	{
		std::istringstream input("EngineOn\nSetGear 1\nSetSpeed 10\nInfo\n");
		WorkCommand workCommand(car, input, output);

		REQUIRE(workCommand.Result().first == WorkCommand::Status(0)); // turn engine on
		REQUIRE(workCommand.Result().first == WorkCommand::Status(0)); // set gear 1
		REQUIRE(workCommand.Result().first == WorkCommand::Status(0)); // set speed 10 moving forward
		REQUIRE(workCommand.Result().first == WorkCommand::Status(0)); // print info

		REQUIRE(output.str() == "Engine: On\nDirection: Forward\nGear: 1\nSpeed: 10\n");
	}
}