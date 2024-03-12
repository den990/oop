#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less) // уровни безопасности
{
	if (arr.empty())
	{
		return false;
	}
	// указатель
	const T* maxElement = &arr[0];
	for (const auto& it : arr)
	{
		if (less(*maxElement, it))
		{
			maxElement = &it;
		}
	}
	maxValue = *maxElement;

	return true;
}