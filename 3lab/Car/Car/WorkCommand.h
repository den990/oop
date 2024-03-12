#pragma once
#include "Car.h"
#include <map>

class WorkCommand
{
public:
	WorkCommand(Car& car, std::istream& input, std::ostream& output);
	enum class Status
	{
		OK,
		EXIT,
		ERROR,
	};

	std::pair<Status, bool> Result();

private:
	enum class Command
	{
		INFO,
		ENGINEON,
		ENGINEOFF,
		SETGEAR,
		SETSPEED,
		EXIT,
		ERROR
	};

	const std::map<std::string, Command> m_mapStringToCommand = {
		{ "info", Command::INFO },
		{ "engineon", Command::ENGINEON },
		{ "engineoff", Command::ENGINEOFF },
		{ "setgear", Command::SETGEAR },
		{ "setspeed", Command::SETSPEED },
		{ "exit", Command::EXIT}
	};

	struct Instruction
	{
		Command command;
		int argument;
	};
	//разобрать с константами
	Instruction GetInstruction();
	Command ParseCommand(std::string& inputCommand);
	void PrintCarInfo() const;
	std::pair<Command, bool> StartInstruction();
	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;

};
