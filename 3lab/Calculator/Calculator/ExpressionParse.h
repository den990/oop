#pragma once
#include <map>
#include <string>
#include <vector>
#include "Result.h"
#include <set>
#include <unordered_map>
#include <cmath>

class ExpressionParse
{
public:
	enum class Command
	{
		DECLAREVARIABLE,
		ASSIGNVARIABLE,
		DECLAREFUNCTION,
		PRINTVALUE,
		PRINTALLVARIABLES,
		PRINTALLFUNCTIONS
	};
	struct ExpressionData
	{
		Command command;
		std::vector<std::string> identifiers;
		double value = DBL_MAX;
		char operation = 'N';
	};
	Result ParseCommand(std::string& inputString, ExpressionData& expressionData);//expressiondata

private:
	const std::map<std::string, Command> m_commandTypeString = {
		{ "var", Command::DECLAREVARIABLE },
		{ "let", Command::ASSIGNVARIABLE },
		{ "fn", Command::DECLAREFUNCTION },
		{ "print", Command::PRINTVALUE },
		{ "printvars", Command::PRINTALLVARIABLES },
		{ "printfns", Command::PRINTALLFUNCTIONS }
	};
	const std::set<char> m_setOperation = {
		'+', '-', '/', '*'
	};
	Result ExistCommand(std::string& commandStr);
	Result ParseAssignVariable(const std::string& inputString, ExpressionData& expressionData) const;
	Result ParseDeclareFunction(const std::string& inputString, ExpressionData& expressionData) const;
	Result ParseDeclareVariable(const std::string& inputString, ExpressionData& expressionData) const;
	bool IsValidIdentifier(const std::string& identifier) const;
	bool IsValidFloat(const std::string& str) const;
};