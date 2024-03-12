#include <iostream>
#include <map>
#include <string>
#include "WorkCommand.h"
#include <algorithm>

WorkCommand::WorkCommand(Car& car, std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_car(car){};

std::pair <WorkCommand::Status, bool> WorkCommand::Result()
{
	std::pair <Command, bool> result = StartInstruction();
	if (result.first == Command::EXIT)
	{
		return { Status::EXIT, true };
	}
	if (result.first == Command::ERROR)
	{
		return { Status::ERROR, true };
	}
	return { Status::OK, result.second };
}
	
WorkCommand::Command WorkCommand::ParseCommand(std::string& inputCommand)
{
	std::transform(inputCommand.begin(), inputCommand.end(), inputCommand.begin(), std::tolower);
	if (m_mapStringToCommand.find(inputCommand) == m_mapStringToCommand.end())
	{
		return Command::ERROR;
	}
	return m_mapStringToCommand.at(inputCommand);
}

WorkCommand::Instruction WorkCommand::GetInstruction() 
{
	std::string instructionStr, command, argument;
	Instruction receivedInstruction = {};
	if (m_input.eof() || instructionStr == "\n")
	{
		return { WorkCommand::Command::EXIT, 0 };
	}
	//упростить
	std::getline(m_input, instructionStr);
	size_t index = instructionStr.find(" ");
	command.append(instructionStr, 0, index);
	if (instructionStr.find(" ") == std::string::npos)
	{
		return { ParseCommand(command), };
	}
	argument.append(instructionStr, index + 1, instructionStr.length());
	return { ParseCommand(command), stoi(argument) };
}

void WorkCommand::PrintCarInfo() const
{
	Car::Direction direction = m_car.GetDirection();
	int gear = m_car.GetGear();

	m_output << "Engine: " << (m_car.IsTurnedOn() ? "On" : "Off") << std::endl
			 << "Direction: " << (direction == Car::Direction::BACKWARD ? "Backward" :
								direction == Car::Direction::FORWARD ? "Forward" :
								"Immobile")
			 << std::endl
			 << "Gear: " << (gear == -1 ? "R" : gear == 0 ? "N" : std::to_string(gear)) << std::endl
			 << "Speed: " << m_car.GetSpeed() << std::endl;
}

std::pair<WorkCommand::Command, bool> WorkCommand::StartInstruction()
{
	WorkCommand::Instruction instruction = GetInstruction();
	switch (instruction.command)
	{
	case Command::ENGINEON:
		return { Command::ENGINEON, m_car.TurnOnEngine() };
	case Command::ENGINEOFF:
		return { Command::ENGINEOFF, m_car.TurnOffEngine() };
	case Command::SETGEAR:
		return { Command::SETGEAR, m_car.SetGear(instruction.argument) };
	case Command::SETSPEED:
		return { Command::SETSPEED, m_car.SetSpeed(instruction.argument) };
	case Command::INFO:
		PrintCarInfo();
		return { Command::INFO, true };
	case Command::EXIT:
		return { Command::EXIT, true };
	default:
		return { Command::ERROR, true };
	}
}