#pragma once
#include <string>
enum class Status
{
	OK,
	UP,
	EXIT,
	ERROR_
};
struct Result
{
	Status status;
	std::string errorMessage;
};