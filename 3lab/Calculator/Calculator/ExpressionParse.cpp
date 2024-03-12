#include "ExpressionParse.h"
#include <algorithm>
#include <regex>

Result ExpressionParse::ExistCommand( std::string& commandStr)
{
	std::transform(commandStr.begin(), commandStr.end(), commandStr.begin(), tolower);
	if (m_commandTypeString.find(commandStr) == m_commandTypeString.end())
	{
		return { Status::ERROR, "Unknown command: " + commandStr + "." };
	}
	return { Status::OK, };
}

Result ExpressionParse::ParseCommand(std::string& inputString, ExpressionData& expressionData)
{
	Result result;
	size_t indexSpace = inputString.find(" ");
	std::string commandStr, argumentStr;
	commandStr.append(inputString, 0, indexSpace);
	if ((result = ExistCommand(commandStr)).status != Status::OK)
	{
		return result;
	}
	Command command = m_commandTypeString.at(commandStr);
	argumentStr.append(inputString, indexSpace + 1, inputString.length());
	switch (command)
	{
	case Command::DECLAREVARIABLE:
		return ParseDeclareVariable(argumentStr, expressionData);
	case Command::ASSIGNVARIABLE:
		return ParseAssignVariable(argumentStr, expressionData);
	case Command::DECLAREFUNCTION:
		return ParseDeclareFunction(argumentStr, expressionData);
	case Command::PRINTVALUE:
		if (!IsValidIdentifier(argumentStr))
		{
			return { Status::ERROR, "Parsing error: Invalid identifier '" +	argumentStr + "'." };
		}
		expressionData = { command, { argumentStr } };
		break;
	case Command::PRINTALLVARIABLES:
		[[fallthrough]];
	case Command::PRINTALLFUNCTIONS:
		expressionData = { command };
	default:
		break;
	}
	return { Status::OK };
	
}


Result ExpressionParse::ParseDeclareVariable(const std::string& inputString, ExpressionData& expressionData) const
{
	if (!IsValidIdentifier(inputString))
	{
		return { Status::ERROR, "Parsing error: Invalid identifier '" + inputString + "'." };
	}
	expressionData = { Command::DECLAREVARIABLE, { inputString } };
	return { Status::OK };
}

Result ExpressionParse::ParseAssignVariable(const std::string& inputString, ExpressionData& expressionData) const // мб переделать название переменной // let
{
	size_t positionEqual = inputString.find("=");
	if (positionEqual == std::string::npos)
	{
		return { Status::ERROR, "Failed to parse assignment " + inputString + "." };
	}
	std::string destIdentifier = inputString.substr(0, positionEqual);

	if (!IsValidIdentifier(destIdentifier))
	{
		return { Status::ERROR, "Parsing error: Invalid identifier '" + destIdentifier + "'." };
	}

	std::string rightPart = inputString.substr(positionEqual + 1);

	if (IsValidIdentifier(rightPart))
	{
		expressionData = { Command::ASSIGNVARIABLE, { destIdentifier, rightPart } };
	}
	else if (IsValidFloat(rightPart))
	{
		double number;
		try
		{
			number = std::stod(rightPart);
		}
		catch (std::out_of_range)
		{
			return { Status::ERROR, "Number is very big" };
		}
		expressionData = { Command::ASSIGNVARIABLE, { destIdentifier }, { number } };
	}
	else
	{
		return { Status::ERROR, "This expression is not parsed" };
	}
	return { Status::OK };
}

Result ExpressionParse::ParseDeclareFunction(const std::string& inputString, ExpressionData& expressionData) const //fn
{
	size_t positionEqual = inputString.find("=");
	if (positionEqual == std::string::npos)
	{
		return { Status::ERROR, "Failed to parse assignment " + inputString + "." };
	}
	std::string fnIdentifier = inputString.substr(0, positionEqual);

	if (!IsValidIdentifier(fnIdentifier))
	{
		return { Status::ERROR, "Parsing error: Invalid identifier '" + fnIdentifier + "'." };
	}

	std::string rightPart = inputString.substr(positionEqual + 1);
	size_t positionOperation;
	for (char operation: m_setOperation)
	{
		if ((positionOperation = rightPart.find(operation)) != std::string::npos)
		{
			std::string firstIdentifier = rightPart.substr(0, positionOperation);
			std::string secondIdentifier = rightPart.substr(positionOperation + 1);
			if (!IsValidIdentifier(firstIdentifier))
			{
				return { Status::ERROR, "Parsing error: Invalid identifier '" + firstIdentifier + "'." };
			}
			if (!IsValidIdentifier(secondIdentifier)) // мб падать из за этой ошибки будет когда прост будем присваивать обычный идентификатор
			{
				return { Status::ERROR, "Parsing error: Invalid identifier '" + secondIdentifier + "'." };
			}
			expressionData = { Command::DECLAREFUNCTION, { fnIdentifier, firstIdentifier, secondIdentifier }, {}, operation };
			return { Status::OK };
		}
	}
	if (!IsValidIdentifier(rightPart))
	{
		return { Status::ERROR, "Parsing error: Invalid identifier '" + rightPart + "'." };
	}
	expressionData = { Command::DECLAREFUNCTION, { fnIdentifier, rightPart } };
	return { Status::OK };
}



bool ExpressionParse::IsValidIdentifier(const std::string& identifier) const
{
	std::regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");

	return std::regex_match(identifier, identifierRegex);
}

bool ExpressionParse::IsValidFloat(const std::string& str) const
{
	std::regex floatRegex("[+-]?([0-9]*[.])?[0-9]+");

	return std::regex_match(str, floatRegex);
}
