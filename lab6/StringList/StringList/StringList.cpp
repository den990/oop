// StringList.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "CStringList.h"

int main()
{
	CStringList tmp;
	tmp.PushBack("Hello");
	tmp.PushBack("World");
	auto tmp1 = tmp.rbegin();
}
