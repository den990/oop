#pragma once
#include <string>

enum class Status
{
	OK,
	ERROR
};

struct Result
{
	Status status;
	std::string errorMessage;
};