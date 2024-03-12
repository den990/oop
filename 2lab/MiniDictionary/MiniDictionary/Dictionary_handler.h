#include <algorithm>
#include <fstream>
#pragma once
#include <iostream>
#include <map>
#include <string>
#include <windows.h>

std::map<std::string, std::string> ReadDictionary(std::istream& fileInput, std::map<std::string, std::string>& dictionary);
void SaveDictionaryToFile(const std::map<std::string, std::string>& dictionary, const std::string& fileName);
void TryAddWord(const std::string& inputString, std::map<std::string, std::string>& dictionary, bool& dictionaryChange, std::istream& input);
void StringToLowerRegister(std::string& inputString);
void ProcessInputString(std::string& inputString, std::map<std::string, std::string>& dictionary, bool& dictionaryChange, std::istream& input);
