// 1.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUS");
    if (argv[1] == NULL) {
        std::cout << "������ ���� ������" << std::endl;
        return 2;
    }
    if (argv[2] == NULL) {
        std::cout << "������ ���� ������" << std::endl;
        return 2;
    }
    std::ifstream fileInput1(argv[1]);
    std::ifstream fileInput2(argv[2]);
    if (!fileInput1) {
        std::cout << "������ ���� �� ������" << std::endl;
        return 2;
    }
    if (!fileInput2) {
        std::cout << "������ ���� �� ������" << std::endl;
        return 2;
    }
    std::string receivedString1, receivedString2;
    int countString = 1;
    while ((!fileInput1.eof()) && (!fileInput2.eof()))
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

// ���������� ����� � ������.
