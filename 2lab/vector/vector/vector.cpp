#include "Proccess.h"
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	std::vector<double> numbers;
	ReadVector(numbers, std::cin);
	if (numbers.size() == 0)
		return 1;
	VectorOperation(numbers);
	std::sort(numbers.begin(), numbers.end()); //почему?
	PrintVector(numbers);
}
