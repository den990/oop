#pragma once
#include "ExpressionParse.h"
class Function
{
public:
	enum class Operation
	{
		ADD,
		SUB,
		MUL,
		DIV
	};
	double NOT_A_NUMBER = std::nan("");
	double CalculateValue(double firstNumber, double secondNumber, Operation operation) const;
private:
	double Multiplication(double firstNumber, double secondNumber) const;
	double Addition(double firstNumber, double secondNumber) const;
	double Substraction(double firstNumber, double secondNumber) const;
	double Division(double firstNumber, double secondNumber) const;
	Operation m_operation;
};