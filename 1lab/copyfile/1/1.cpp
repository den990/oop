﻿// 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RUS");
    if (argv[1] == NULL){
        std::cout << "Входной файл пустой" << std::endl;
        return 1;
    }
    if (argv[2] == NULL){
        std::cout << "Выходной файл пустой" << std::endl;
        return 1;
    }
    std::ifstream fileInput(argv[1]);
    if (!fileInput) {
        std::cout << "Входной файл не открыт" << std::endl;
    }
    std::ofstream fileOutput(argv[2]);
    std::string receivedString;
    while (fileInput >> receivedString){
        fileOutput << receivedString << std::endl;
    }
    fileInput.close(), fileOutput.close();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
