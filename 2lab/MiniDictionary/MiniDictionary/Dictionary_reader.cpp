#include <string>
#include <windows.h>
#include <fstream>

std::string ReadInputString(std::istream& input)
{
	std::string inputString;
	getline(input, inputString);
	return inputString;
}