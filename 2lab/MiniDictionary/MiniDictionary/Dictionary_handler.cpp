#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <windows.h>//
#include "Dictionary_reader.h"

std::map<std::string, std::string> ReadDictionary(std::istream& fileInput, std::map<std::string, std::string>& dictionary) // ������� �� ���������� � ������� ����� ������ �������
{
	std::string str;
	while (getline(fileInput, str))
	{
		size_t position = str.find("-");
		if (position != std::string::npos)
		{
			std::string word = str.substr(0, position - 1);
			std::string translateWord = str.substr(position + 2);
			dictionary[word] = translateWord;
		}
	}
	return dictionary;
}

void SaveDictionaryToFile(const std::map<std::string, std::string>& dictionary, const std::string& fileName)
{
	std::ofstream fileOutput(fileName);
	if (fileOutput)
	{
		for (const auto& [word, translateWord] : dictionary)
		{
			fileOutput << word << " - " << translateWord << std::endl;
		}
		std::cout << "��������� ���������. �� ��������." << std::endl;
	}
	else
	{
		std::cout << "���� �� ������, ��������� �� ���������" << std::endl;
	}
}


//dictionaryChange?
void TryAddWord(const std::string& inputString, std::map<std::string, std::string>& dictionary, bool& dictionaryChange, std::istream& input)//TryAddWord
{
	std::cout << "����������� ����� \"" << inputString << "\". ������� ������� ��� ������ ������ ��� ������." << std::endl;
	std::string inputNewWord = ReadInputString(input);
	if (!inputNewWord.empty())
	{
		dictionary[inputString] = inputNewWord;
		dictionaryChange = true;
		std::cout << "����� \"" << inputString << "\" ��������� � ������� ��� \"" << inputNewWord << "\"." << std::endl;
	}
	else
	{
		std::cout << "����� \"" << inputString << "\" ���������������." << std::endl;
	}
}

void StringToLowerRegister(std::string& inputString)
{
	std::transform(inputString.begin(), inputString.end(), inputString.begin(), std::tolower);
}

void ProcessInputString(std::string& inputString, std::map<std::string, std::string>& dictionary, bool& dictionaryChange, std::istream& input)
{
	StringToLowerRegister(inputString);
	auto resultFind = dictionary.find(inputString);
	if (resultFind != dictionary.end())
	{
		std::cout << dictionary[inputString] << std::endl;
	}
	else
	{
		TryAddWord(inputString, dictionary, dictionaryChange, input);
	}
}
