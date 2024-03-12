#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

int ValidationArguments(int argc)
{
    if (argc != 5)
    {
        std::cout << "Error, enter the argumets: <input file> <output file> <search string> <replace string>" << std::endl;
        return 1;
    }
    return 0;
}

void Replace(std::istream& input, std::ostream& output, std::string& findWord, std::string& replaceWord)
{
    std::string str;
    if (replaceWord != "")
    {
        while (getline(input, str))
        {
            std::string newStr;
            int saveIndexAfterFindWord = 0;
            size_t index = 0;
            while ((index = str.find(findWord, index)) != std::string::npos)
            {
                newStr.append(str, saveIndexAfterFindWord, index - saveIndexAfterFindWord);
                index += findWord.length();
                saveIndexAfterFindWord = index;
                newStr += replaceWord;
            }
            if (saveIndexAfterFindWord != str.length())
            {
                newStr.append(str, saveIndexAfterFindWord, index);
            }
            output << newStr << std::endl;
        }
    }
    else
    {
        while (getline(input, str))
        {
            output << str << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int result = ValidationArguments(argc);
    if (result == 1) return 1;
    std::ifstream fileInput(argv[1]);
    std::ofstream fileOutput(argv[2]);

    if ((!fileInput) ||(!fileOutput))// проверить и выходной файл
    {
        std::cout << "File(-s) not open" << std::endl;
        return 1;
    }

    std::string findWord = argv[3], replaceWord = argv[4];
    Replace(fileInput, fileOutput, findWord, replaceWord);
    return 0;
}