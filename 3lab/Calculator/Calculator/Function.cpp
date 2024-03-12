#include "Function.h"

double Function::CalculateValue(double firstNumber, double secondNumber, Operation operation) const
{
	switch (operation)
	{
	case Operation::ADD:
		return Addition(firstNumber, secondNumber);
	case Operation::SUB:
		return Substraction(firstNumber, secondNumber);
		break;
	case Operation::MUL:
		return Multiplication(firstNumber, secondNumber);
		break;
	case Operation::DIV:
		return Division(firstNumber, secondNumber);
		break;
	default:
		return NOT_A_NUMBER; // nan
	}
}

double Function::Multiplication(double firstNumber, double secondNumber) const
{
	double result = firstNumber * secondNumber;
	if (firstNumber == 0 || secondNumber == 0 || abs(result) >= DBL_MIN)
	{
		return result;
	}
	double ah = firstNumber / 2;
	double bh = secondNumber / 2;
	double al = firstNumber - ah;
	double bl = secondNumber - bh;
	double ph = ah * bh;
	double pm = (ah + al) * (bh + bl) - ph;
	return 2 * (ph - pm) + result;
}

double Function::Addition(double firstNumber, double secondNumber) const
{
	double s = firstNumber + secondNumber;
	double d = firstNumber - s + secondNumber;
	return s + d;
}

double Function::Substraction(double firstNumber, double secondNumber) const
{
	double s = firstNumber - secondNumber;
	double d = firstNumber - s - secondNumber;
	return s + d;
}

double Function::Division(double firstNumber, double secondNumber) const
{
	if (secondNumber == 0)
	{
		return NOT_A_NUMBER; 
	}
	double q = firstNumber / secondNumber;
	if (secondNumber == 1  || secondNumber == -1 || abs(q) >= DBL_MIN)
	{
		return q;
	}
	double r = firstNumber - q * secondNumber;
	double t = r + secondNumber;
	return q + t / secondNumber;
}