#include <fstream>
#include <map>
#include <iostream>
#include "Dictionary_handler.h"
#include "Dictionary_reader.h"

const std::string End = "...";

void FillingWord(std::istream& input, std::map<std::string, std::string>& dictionary, std::string fileName)
{
	bool dictionaryChange = false;
	while (1)
	{
		std::string inputString = ReadInputString(input);
		if (input.eof())
		{
			return;
		}
		if (inputString == End)
		{
			if (dictionaryChange)
			{
				std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << std::endl;
				getline(input, inputString);
				if (inputString == "Y" || inputString == "y")
				{
					SaveDictionaryToFile(dictionary, fileName);
				}
			}
			break;
		}
		if (inputString == "")
		{
			std::cout << "������� �����" << std::endl;
		}
		else
		{
			ProcessInputString(inputString, dictionary, dictionaryChange, input);
		}
	}
}