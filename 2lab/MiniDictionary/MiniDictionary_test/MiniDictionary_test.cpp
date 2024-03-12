#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../MiniDictionary/Dictionary_handler.h"
#include "../MiniDictionary/Dictionary_reader.h"
#include "../MiniDictionary/Dictionary_fill.h"
#include <iostream>
#include <sstream>
#include <windows.h>

TEST_CASE("ReadInputString function")
{
	setlocale(LC_ALL, "RUS");
	SECTION("Read empty string")
	{
		std::istringstream input("");
		REQUIRE(ReadInputString(input) == "");
		REQUIRE(ReadInputString(input).empty());
	}
	SECTION("Read string")
	{
		std::istringstream input("hello");
		REQUIRE(ReadInputString(input) == "hello");
	}
}

TEST_CASE("SaveDictionaryToFile function")
{
	setlocale(LC_ALL, "RUS");
	SECTION("Save empty file")
	{
		std::map<std::string, std::string> dictionary;
		std::string fileName = "test_dictionary.txt";
		SaveDictionaryToFile(dictionary, fileName);
		std::ifstream file(fileName);
		REQUIRE(file.peek() == EOF);
	}
	SECTION("Save file with traslate")
	{
		std::map<std::string, std::string> dictionary = { { "hello", "привет" }, { "world", "мир" } };
		std::string fileName = "test_dictionary.txt";
		SaveDictionaryToFile(dictionary, fileName);
		std::ifstream file(fileName);
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string fileContents = buffer.str();
		REQUIRE(fileContents.find("hello - привет") != std::string::npos);
		REQUIRE(fileContents.find("world - мир") != std::string::npos);
	}
}

TEST_CASE("TryAddWord function")
{
	setlocale(LC_ALL, "RUS");
	SECTION("Empty string")
	{
		std::map<std::string, std::string> dictionary;
		std::string inputString;
		std::istringstream input("");
		bool dictionaryChange = false;
		TryAddWord(inputString, dictionary, dictionaryChange, input);
		REQUIRE(dictionaryChange == false);
	}
	SECTION("Word not translated")
	{
		std::map<std::string, std::string> dictionary = { { "hello", "привет" }, { "world", "мир" } };
		std::string inputString = "ball";
		std::istringstream input("мяч");
		bool dictionaryChange = false;
		TryAddWord(inputString, dictionary, dictionaryChange, input);
		REQUIRE(dictionaryChange == true);
		REQUIRE(dictionary.find(inputString) != dictionary.end());
	}
}

TEST_CASE("StringToLowerRegister function")
{
	std::string inputString;
	SECTION("Empty string")
	{
		StringToLowerRegister(inputString);
		REQUIRE(inputString == "");
	}
	SECTION("Lower String")
	{
		inputString = "hello";
		StringToLowerRegister(inputString);
		REQUIRE(inputString == "hello");
	}
	SECTION("Upper String")
	{
		inputString = "HELLO";
		StringToLowerRegister(inputString);
		REQUIRE(inputString == "hello");
	}
	SECTION("String with upper symbols")
	{
		inputString = "heLlO";
		StringToLowerRegister(inputString);
		REQUIRE(inputString == "hello");
	}
}

TEST_CASE("ProcessInputString function")
{
	setlocale(LC_ALL, "RUS");
	SECTION("Empty string")
	{
		std::map<std::string, std::string> dictionary = { { "hello", "привет" }, { "world", "мир" } };
		std::string inputString = "";
		std::istringstream input("");
		bool dictionaryChange = false;
		ProcessInputString(inputString, dictionary, dictionaryChange, input);
		REQUIRE(dictionaryChange == false);
	}
	SECTION("Dictionary have translation")
	{
		std::map<std::string, std::string> dictionary = { { "hello", "привет" }, { "world", "мир" }, { "ball", "мяч" } };
		std::string inputString = "ball";
		std::istringstream input("мяч");
		bool dictionaryChange = false;
		ProcessInputString(inputString, dictionary, dictionaryChange, input);
		REQUIRE(dictionaryChange == false);
		REQUIRE(dictionary.find(inputString) != dictionary.end());
	}
	SECTION("Dictionary not have translation")
	{
		std::map<std::string, std::string> dictionary = { { "hello", "привет" }, { "world", "мир" }, { "ball", "мяч" } };
		std::string inputString = "space";
		std::istringstream input("космос");
		bool dictionaryChange = false;
		ProcessInputString(inputString, dictionary, dictionaryChange, input);
		REQUIRE(dictionaryChange == true);
		REQUIRE(dictionary.find(inputString) != dictionary.end());
	}
	SECTION("Word not translated")
	{
		std::map<std::string, std::string> dictionary = { { "hello", "привет" }, { "world", "мир" }, { "ball", "мяч" } };
		std::string inputString = "space";
		std::istringstream input("");
		bool dictionaryChange = false;
		ProcessInputString(inputString, dictionary, dictionaryChange, input);
		REQUIRE(dictionaryChange == false);
		REQUIRE(dictionary.find(inputString) == dictionary.end());
	}
}

TEST_CASE("FillingWord function")
{
	setlocale(LC_ALL, "RUS");
	std::string fileName = "test_dictionary.txt";
	std::ifstream MiniDictionary(fileName);
	std::stringstream buffer;
	SECTION("Add empty string")
	{
		std::map<std::string, std::string> dictionary = { { "ball", "мяч" } }, dictionaryInput = { { "ball", "мяч" } };
		std::istringstream input("\n...");
		FillingWord(input, dictionary, fileName);
		REQUIRE(dictionary == dictionaryInput);
	}
	SECTION("Add new translate")
	{
		std::map<std::string, std::string> dictionary = { { "ball", "мяч" } }, dictionaryInput = { { "ball", "мяч" }, { "space", "космос" } };
		std::istringstream input("space\nкосмос\n...\nY");
		FillingWord(input, dictionary, fileName);
		buffer << MiniDictionary.rdbuf();
		std::string fileContents = buffer.str();
		REQUIRE(fileContents.find("space - космос") != std::string::npos);
		REQUIRE(dictionary == dictionaryInput);
	}
	SECTION("Add existing translate")
	{
		std::map<std::string, std::string> dictionary = { { "hello", "привет" }, { "world", "мир" }, { "ball", "мяч" } }, dictionaryInput = { { "hello", "привет" }, { "world", "мир" }, { "ball", "мяч" } };
		std::istringstream input("hello\n...");
		FillingWord(input, dictionary, fileName);
		buffer << MiniDictionary.rdbuf();
		std::string fileContents = buffer.str();
		REQUIRE(dictionary == dictionaryInput);
	}
}