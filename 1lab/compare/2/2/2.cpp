// 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUS");
    if (argv[1] == NULL) {
        std::cout << "Первый файл пустой" << std::endl;
        return 2;
    }
    if (argv[2] == NULL) {
        std::cout << "Второй файл пустой" << std::endl;
        return 2;
    }
    std::ifstream fileInput1(argv[1]);
    std::ifstream fileInput2(argv[2]);
    if (!fileInput1) {
        std::cout << "Первый файл не открыт" << std::endl;
        return 2;
    }
    if (!fileInput2) {
        std::cout << "Второй файл не открыт" << std::endl;
        return 2;
    }
    std::string receivedString1, receivedString2;
    int countString = 1, countStringInFile1 = 1, countStringInFile2 = 1, maxCountString = 0;
    while ((!fileInput1.eof()) && (!fileInput2.eof()))
    {
        if (fileInput1 >> receivedString1)
        {
            countStringInFile1++;
        }
        if (fileInput2 >> receivedString2)
        {
            countStringInFile2++;
        }
    }
    if (countStringInFile1 > countStringInFile2)
    {
        maxCountString = countStringInFile1;
    }
    else
    {
        maxCountString = countStringInFile2;
    }
    fileInput1.clear(), fileInput1.seekg(0);
    fileInput2.clear(), fileInput2.seekg(0);
    while (countString <= maxCountString)
    {
        fileInput1 >> receivedString1, fileInput2 >> receivedString2;
        if (receivedString1 == receivedString2)
        {
            countString++;
        }
        else
        {
            std::cout << "Files are different. Line number is " << countString << std::endl;
            return 2;
        }
    }
    std::cout << "Files are equal" << std::endl;
    fileInput1.close(), fileInput2.close();
}

// количество строк в файлах.
