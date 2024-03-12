#include <algorithm>
#include <iostream>
#include <vector>

void ReadVector(std::vector<double>& numbers, std::istream& input)
{
	if (input.peek() == EOF)
	{
		return;
	}
	while (!input.eof())
	{
		double number;
		if (input >> number)
		{
			numbers.push_back(number);
		}
		else
		{
			break;
		}
	}
}

void VectorOperation(std::vector<double>& numbers)
{
	if (numbers.size() == 0)
		return;
	double maxNumber = *std::max_element(numbers.begin(), numbers.end()) / 2;
	std::transform(numbers.begin(), numbers.end(), numbers.begin(),
		[=](double number) { return (number / (maxNumber)); }); // clangformat не было длинных строчек
}

void PrintVector(std::vector<double>& numbers)
{
	copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));
}
