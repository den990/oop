#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

int ValidationArguments(int argc)
{
	if (argc < 2)
	{
		std::cout << "Eror, please enter: flipbyte.exe <input byte>" << std::endl;
		return 1;
	}
	return 0;
}

bool ToInteger(const char* s, int& number)
{
	char* withoutChar = NULL;
	number = strtol(s, &withoutChar, 10);
	return (*withoutChar == NULL);
}


bool IsUnsignedChar(const char* strNum, unsigned char& returnNumber)
{
	 int tempNumber;

	if (!ToInteger(strNum, tempNumber))
	{
		std::cout << "Введённое значение не число" << std::endl;
		return false;
	}
	if ((tempNumber < 0) || (tempNumber > 255))
	{
		std::cout << "Число не входит в диапозон от 0 до 255" << std::endl;;
		return false;
	}

	returnNumber = (unsigned char) tempNumber;
	return true;
}

unsigned char ReverseByte(unsigned char& n)
{
	unsigned char k = 0;
	k = ((n & 0b00001111) << 4) | ((n & 0b11110000) >> 4);
	k = ((k & 0b00110011) << 2) | ((k & 0b11001100) >> 2);
	k = ((k & 0b01010101) << 1) | ((k & 0b10101010) >> 1);
	return k;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int result = ValidationArguments(argc);
	if (result == 1) return 1;
	unsigned char curNumber;
	if (!IsUnsignedChar(argv[1], curNumber))
	{
		return 1;
	}
	unsigned char flippedNumber = ReverseByte(curNumber);	
	std::ofstream fileOutput(argv[2]);
	fileOutput << int(flippedNumber);
	return 0;
}

