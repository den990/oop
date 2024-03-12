#include <iostream>
#include <set>
#include <sstream>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<bool> isPrime(upperBound + 1, true);
	isPrime[0] = isPrime[1] = false; // 0 и 1 не €вл€ютс€ простыми числами
	for (size_t i = 2; i * i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			for (size_t j = i * i; j <= upperBound; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	std::set<int> primes;
	for (int i = 2; i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			primes.insert(primes.end(), i);
		}
	}
	return primes;
}

void PrintPrimeNumbers(const std::set<int>& primes, std::ostream& output)
{
	std::ostringstream oss;
	for (int prime : primes)
	{
		oss << prime << ", ";
	}
	output << oss.str() << std::endl;
}