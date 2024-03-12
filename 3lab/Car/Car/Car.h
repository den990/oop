#pragma once
#include <string>

class Car
{
public:
	enum class Direction
	{
		FORWARD,
		BACKWARD,
		IMMOBILE
	};
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	bool IsTurnedOn() const;
	Direction GetDirection();// лучше возвращать enum
	int GetSpeed() const;
	int GetGear() const;
	std::string GetLastErrorMessage() const;

private:
	int m_gear = 0;
	int m_speed = 0;
	bool m_isEngineOn = false;
	std::string m_lastErrorMessage;
};