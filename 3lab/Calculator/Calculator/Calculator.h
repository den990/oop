#pragma once
#include "Result.h"
#include <iostream>
#include "Function.h"
#include "ExpressionParse.h"
#include <algorithm>
class Calculator
{
public:
	Calculator(ExpressionParse& m_parser, std::istream& input, std::ostream& output);
	void Interpret();
private:
	struct functions
	{
		std::string name;
		std::vector<std::string> identificators;
		char operation;
		double value = DBL_MAX;
	};
	Result ExecutCommand(ExpressionParse::ExpressionData& expressionData);
	Result ExecuteFunctionDeclaration(const ExpressionParse::ExpressionData& expressionData);
	Result ExecuteDeclareVariable(const ExpressionParse::ExpressionData& expressionData);
	Result ExecuteAssignVariable(const ExpressionParse::ExpressionData& expressionData);
	Result ExecutePrintValue(const ExpressionParse::ExpressionData& expressionData, std::ostream& output);
	Result ExecutePrintAllVariables(std::ostream& output) const;
	Result ExecutePrintAllFunctions(std::ostream& output);
	bool FirstAdd(functions* it, std::map<std::string, double>& mapValueFunctions);
	bool FunctionEqualVariable(functions* it, std::map<std::string, double>& mapValueFunctions);
	bool FunctionAndVariable(functions* it, std::map<std::string, double>& mapValueFunctions);
	bool FunctionWithEqualVariablesOrFunctions(functions* it, std::map<std::string, double>& mapValueFunctions);
	Result FunctionEvalution(std::map<std::string, double>& printFunction);
	Result FindValueFunctions(const char& ident, double firstNumber, double secondNumber, double& result);
	Function m_function;
	ExpressionParse& m_parser;
	std::istream& m_input;
	std::ostream& m_output;
	std::map<std::string, double> m_variables;
	std::vector<functions> m_functions;
};
