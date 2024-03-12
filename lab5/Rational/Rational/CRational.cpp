#include "CRational.h"
#include <stdexcept>
constexpr int intMin = std::numeric_limits<int>::min();
constexpr int intMax = std::numeric_limits<int>::max();

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("denominator cannot be 0");
	}
	if (denominator < 0)
	{
		numerator *= -1;
		denominator = std::abs(denominator);
	}
	m_numerator = numerator;
	m_denominator = denominator;
	NormalizeRational();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

CRational CRational::operator+() const
{
	return *this;
}

CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}


CRational operator+(const CRational& number1, const CRational& number2)
{
	int numerator = number1.GetNumerator() * number2.GetDenominator() + number2.GetNumerator() * number1.GetDenominator();
	int denominator = number1.GetDenominator() * number2.GetDenominator();
	return CRational(numerator, denominator);
}

CRational operator-(const CRational& number1, const CRational& number2)
{
	int numerator = number1.GetNumerator() * number2.GetDenominator() - number2.GetNumerator() * number1.GetDenominator();
	int denominator = number1.GetDenominator() * number2.GetDenominator();
	return CRational(numerator, denominator);
}

CRational operator*(const CRational& number1, const CRational& number2)
{
	int numerator = number1.GetNumerator() * number2.GetNumerator();
	int denominator = number1.GetDenominator() * number2.GetDenominator();
	return CRational(numerator, denominator);
}

CRational operator/(const CRational& number1, const CRational& number2)
{
	int numerator = number1.GetNumerator() * number2.GetDenominator();
	int denominator = number1.GetDenominator() * number2.GetNumerator();
	return CRational(numerator, denominator);
}


CRational& CRational::operator+=(const CRational& number)
{
	*this = *this + number;
	return *this;
}

CRational& CRational::operator-=(const CRational& number)
{
	*this = *this - number;
	return *this;
}

CRational& CRational::operator*=(const CRational& number)
{
	*this = *this * number;
	return *this;
}

CRational& CRational::operator/=(const CRational& number)
{
	*this = *this / number;
	return *this;
}

bool operator==(const CRational& number1, const CRational& number2)
{
	return (number1.GetNumerator() * number2.GetDenominator() == number2.GetNumerator() * number1.GetDenominator());
}


bool operator!=(const CRational& number1, const CRational& number2)
{
	return !(number1 == number2);
}


bool operator<(const CRational& number1, const CRational& number2)
{
	return (number1.GetNumerator() * number2.GetDenominator() < number2.GetNumerator() * number1.GetDenominator());
}

bool operator>(const CRational& number1, const CRational& number2)
{
	return (number1.GetNumerator() * number2.GetDenominator() > number2.GetNumerator() * number1.GetDenominator());
}

bool operator<=(const CRational& number1, const CRational& number2)
{
	return !(number1 > number2);
}

bool operator>=(const CRational& number1, const CRational& number2)
{
	return !(number1 < number2);
}

std::istream& operator>>(std::istream& is, CRational& number)
{
	int numerator, denominator;
	if (is >> numerator && is.get() == '/' && is >> denominator)
	{
		number = CRational(numerator, denominator);
	}
	else
		is.setstate(std::ios_base::failbit);
	return is;
}

std::ostream& operator<<(std::ostream& os, const CRational& number)
{
	os << number.GetNumerator() << "/" << number.GetDenominator();
	return os;
}

//int CRational::GetNOD(int number1, int number2) //std::gdk
//{
//	while (number2 != 0)
//	{
//		std::swap(number1, number2);
//		number2 = number2 % number1;
//	}
//	return (number1 != 0) ? number1 : 1;
//}

void CRational::NormalizeRational()
{
	int nod = std::gcd(m_numerator, m_denominator);
	m_numerator /= nod;
	m_denominator /= nod;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator / m_denominator);
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	std::pair<int, CRational> result;
	result.first = m_numerator / m_denominator;
	int numerator = m_numerator - result.first * m_denominator;
	result.second = CRational(numerator, m_denominator);
	return result;
}



