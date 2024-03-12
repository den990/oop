#pragma once
#include <utility>
#include <iostream>
#include <string>
#include <numeric>

class CRational
{
public:
	// Конструирует рациональное число, равное нулю (0/1)
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const; //выделяем целую часть
	CRational operator+() const;
	CRational operator-() const;

	friend CRational operator+(const CRational& number1, const CRational& number2);
	friend CRational operator-(const CRational& number1, const CRational& number2);

	friend CRational operator*(const CRational& number1, const CRational& number2);
	friend CRational operator/(const CRational& number1, const CRational& number2);

	CRational& operator+=(const CRational& number);
	CRational& operator-=(const CRational& number);
	CRational& operator*=(const CRational& number);
	CRational& operator/=(const CRational& number);

	friend bool operator==(const CRational& number1, const CRational& number2);
	friend bool operator!=(const CRational& number1, const CRational& number2);
	friend bool operator<(const CRational& number1, const CRational& number2);
	friend bool operator>(const CRational& number1, const CRational& number2);
	friend bool operator<=(const CRational& number1, const CRational& number2);
	friend bool operator>=(const CRational& number1, const CRational& number2);

	friend std::istream& operator>>(std::istream& is, CRational& number);
	friend std::ostream& operator<<(std::ostream& os, const CRational& number);
	~CRational() = default;

private:
	/*int GetNOD(int number1, int number2);*/
	void NormalizeRational();

	int m_numerator;
	int m_denominator;
};


