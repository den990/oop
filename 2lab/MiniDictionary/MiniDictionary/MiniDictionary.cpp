#include "Dictionary_handler.h"
#include "Dictionary_reader.h"
#include "Dictionary_fill.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <windows.h>
const std::string DEFAULT_FILE_NAME = "MiniDictionary.txt";

int ValidationArguments(int argc)
{
	if (argc != 2)
	{
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::map<std::string, std::string> dictionary;
	int result = ValidationArguments(argc);
	std::string fileName;
	if (result == 0)
	{
		fileName = argv[1];
		std::ifstream fileInput(fileName);
		if (fileInput)
		{
			dictionary = ReadDictionary(fileInput, dictionary);
		}
		else
		{
			std::cout << "Файл не открыт" << std::endl;
			return 1;
		}
	}
	else
	{
		std::cout << "Файл не указан, создаем новый" << std::endl;
		fileName = DEFAULT_FILE_NAME;
	}
	FillingWord(std::cin, dictionary, fileName);
}