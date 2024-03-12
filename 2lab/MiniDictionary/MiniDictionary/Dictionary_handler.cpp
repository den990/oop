#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <windows.h>//
#include "Dictionary_reader.h"

std::map<std::string, std::string> ReadDictionary(std::istream& fileInput, std::map<std::string, std::string>& dictionary) // убираем из параметров и создаем новый внутри функции
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
		std::cout << "Изменения сохранены. До свидания." << std::endl;
	}
	else
	{
		std::cout << "Файл не открыт, изменения не сохранены" << std::endl;
	}
}


//dictionaryChange?
void TryAddWord(const std::string& inputString, std::map<std::string, std::string>& dictionary, bool& dictionaryChange, std::istream& input)//TryAddWord
{
	std::cout << "Неизвестное слово \"" << inputString << "\". Введите перевод или пустую строку для отказа." << std::endl;
	std::string inputNewWord = ReadInputString(input);
	if (!inputNewWord.empty())
	{
		dictionary[inputString] = inputNewWord;
		dictionaryChange = true;
		std::cout << "Слово \"" << inputString << "\" сохранено в словаре как \"" << inputNewWord << "\"." << std::endl;
	}
	else
	{
		std::cout << "Слово \"" << inputString << "\" проигнорировано." << std::endl;
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
