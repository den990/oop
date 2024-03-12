#include "Calculator.h"

Calculator::Calculator(ExpressionParse& parser, std::istream& input, std::ostream& output) // expression переименовать
	: m_input(input)
	, m_output(output)
	, m_parser(parser){};

void Calculator::Interpret()
{
	std::string inputString;
	getline(m_input, inputString);
	if (inputString.empty())
	{
		return;
	}
	Result result;
	ExpressionParse::ExpressionData expression;
	if ((result = m_parser.ParseCommand(inputString, expression)).status != Status::OK)
	{
		m_output << result.errorMessage << std::endl;
		return;
	}
	if ((result = ExecutCommand(expression)).status != Status::OK)
	{
		m_output << result.errorMessage << std::endl;
		return;
	}
}

Result Calculator::ExecutCommand(ExpressionParse::ExpressionData& expressionData)
{
	switch (expressionData.command)
	{
	case ExpressionParse::Command::DECLAREFUNCTION:
		return ExecuteFunctionDeclaration(expressionData);
	case ExpressionParse::Command::DECLAREVARIABLE:
		return ExecuteDeclareVariable(expressionData);
	case ExpressionParse::Command::ASSIGNVARIABLE:
		return ExecuteAssignVariable(expressionData);
	case ExpressionParse::Command::PRINTVALUE:
		return ExecutePrintValue(expressionData, m_output);
	case ExpressionParse::Command::PRINTALLFUNCTIONS:
		return ExecutePrintAllFunctions(m_output);
	case ExpressionParse::Command::PRINTALLVARIABLES:
		return ExecutePrintAllVariables(m_output);
	}
}

Result Calculator::ExecuteFunctionDeclaration(const ExpressionParse::ExpressionData& expressionData) // надо добавить еще где просто = без умножения и т.д
{
	for (size_t index = 0; index < m_functions.size(); index++)
	{
		if (m_functions[index].name == expressionData.identifiers[0])
		{
			return { Status::ERROR, "This function is exist" };
		}
	}
	if (expressionData.identifiers.size() > 2)
	{
		m_functions.push_back({ expressionData.identifiers[0], { expressionData.identifiers[1], expressionData.identifiers[2] }, expressionData.operation });
	}
	else
	{
		m_functions.push_back({ expressionData.identifiers[0], { expressionData.identifiers[1] }, expressionData.operation });
	}
	return { Status::OK };
}

Result Calculator::ExecuteDeclareVariable(const ExpressionParse::ExpressionData& expressionData)
{
	if (m_variables.find(expressionData.identifiers[0]) == m_variables.end())
	{
		m_variables[expressionData.identifiers[0]] = nan("");
		return { Status::OK };
	}
	else
	{
		return { Status::ERROR, "This variable is exist" };
	}
}

Result Calculator::ExecuteAssignVariable(const ExpressionParse::ExpressionData& expressionData) // может быть идентификатором и числом
{
	if (expressionData.value != DBL_MAX)
	{
		m_variables[expressionData.identifiers[0]] = expressionData.value;
		return { Status::OK };
	}
	if (m_variables.find(expressionData.identifiers[1]) != m_variables.end())
	{
		m_variables[expressionData.identifiers[0]] = m_variables[expressionData.identifiers[1]];
	}
	else
	{
		for (size_t index = 0; index < m_functions.size(); index++) //заменить на find
		{

			if (m_functions[index].name == expressionData.identifiers[1])
			{
				std::map<std::string, double> mapValueFunctions;
				FunctionEvalution(mapValueFunctions);
				m_variables[expressionData.identifiers[0]] = mapValueFunctions[expressionData.identifiers[1]];
				return { Status::OK };
			}
		}
		return { Status::ERROR, "This variable is not exist" };
	}
}

Result Calculator::ExecutePrintValue(const ExpressionParse::ExpressionData& expressionData, std::ostream& output) //избавиться где можно от вложенности
{
	if (m_variables.find(expressionData.identifiers[0]) != m_variables.end())
	{
		output << m_variables.at(expressionData.identifiers[0]) << std::endl;
		return { Status::OK };
	}
	for (size_t index = 0; index < m_functions.size(); index++)
	{
		if (m_functions[index].name == expressionData.identifiers[0])
		{
			std::map<std::string, double> mapValueFunctions;
			FunctionEvalution(mapValueFunctions);
			output << mapValueFunctions[expressionData.identifiers[0]] << std::endl;
			return { Status::OK };
		}
	}
	return { Status::ERROR, "This value does not exist" };
}

bool Calculator::FirstAdd(functions* it, std::map<std::string, double>& mapValueFunctions) //хаписываем первое
{
	double result;
	if (m_variables.find(it->identificators.at(0)) != m_variables.end() && (m_variables.find(it->identificators.at(1)) != m_variables.end())) //проходим в один раз сначала т.к функции заполняются сначала и первая функция состоит из var
	{
		FindValueFunctions(it->operation, m_variables.at(it->identificators.at(0)), m_variables.at(it->identificators.at(1)), result);
		mapValueFunctions[it->name] = result;
		return true;
	}
	return false;
}

bool Calculator::FunctionEqualVariable(functions* it, std::map<std::string, double>& mapValueFunctions)//fn name=var
{
	if (m_variables.find(it->identificators.at(0)) != m_variables.end())
	{
		mapValueFunctions[it->name] = m_variables[it->identificators.at(0)];
		return true;
	}
	return false;
}

bool Calculator::FunctionAndVariable(functions* it, std::map<std::string, double>& mapValueFunctions)// fn=map(2)*var(1) ,fn=var(1)*map(2)
{
	double result;
	if (((mapValueFunctions.find(it->identificators.at(1)) != mapValueFunctions.end()) && ((m_variables.find(it->identificators.at(0)) != m_variables.end()))) || 
		((mapValueFunctions.find(it->identificators.at(0)) != mapValueFunctions.end()) && ((m_variables.find(it->identificators.at(1)) != m_variables.end()))))
	{
		if (mapValueFunctions.find(it->identificators.at(1)) != mapValueFunctions.end() && (m_variables.find(it->identificators.at(0)) != m_variables.end()))
		{
			FindValueFunctions(it->operation, m_variables.at(it->identificators.at(0)), mapValueFunctions.at(it->identificators.at(1)), result);
			mapValueFunctions[it->name] = result;
			return true;
		}
		else if (mapValueFunctions.find(it->identificators.at(0)) != mapValueFunctions.end() && (m_variables.find(it->identificators.at(1)) != m_variables.end()))
		{
			FindValueFunctions(it->operation, mapValueFunctions.at(it->identificators.at(0)), m_variables.at(it->identificators.at(1)), result);
			mapValueFunctions[it->name] = result;
			return true;
		}
	}
	return false;
}

bool Calculator::FunctionWithEqualVariablesOrFunctions(functions* it, std::map<std::string, double>& mapValueFunctions)
{
	double result;
	if ((mapValueFunctions.find(it->identificators.at(0)) != mapValueFunctions.end() && (mapValueFunctions.find(it->identificators.at(0)) != mapValueFunctions.end()))) // fn name=fn*fn;
	{
		FindValueFunctions(it->operation, mapValueFunctions.at(it->identificators.at(0)), mapValueFunctions.at(it->identificators.at(1)), result);
		mapValueFunctions[it->name] = result;
		return true;
	}
	else if ((m_variables.find(it->identificators.at(0)) != m_variables.end() && (m_variables.find(it->identificators.at(0)) != m_variables.end()))) // fn name=x*x
	{
		FindValueFunctions(it->operation, m_variables.at(it->identificators.at(0)), m_variables.at(it->identificators.at(1)), result);
		mapValueFunctions[it->name] = result;
		return true;
	}
	return false;
}

Result Calculator::FunctionEvalution(std::map<std::string, double>& mapValueFunctions)
{
	for (auto it = m_functions.cbegin(); it != m_functions.cend(); ++it)
	{
		if (it->identificators.size() > 1)
		{
			if (FirstAdd(it._Ptr, mapValueFunctions))
			{
				continue;
			}
		}
		else
		{
			if (FunctionEqualVariable(it._Ptr, mapValueFunctions))
			{
				continue;
			}
			else
			{
				return { Status::ERROR, "This variable does not exist" };
			}
		}

		if (FunctionAndVariable(it._Ptr, mapValueFunctions))
		{
			continue;
		}

		if (FunctionWithEqualVariablesOrFunctions(it._Ptr, mapValueFunctions))
		{
			continue;
		}

	}
	return { Status::OK };
}

	Result Calculator::ExecutePrintAllFunctions(std::ostream & output) // нужно в конце высчитывать в конце идентификаторов, и задается формулой
	{
		std::map<std::string, double> mapValueFunctions;
		if (m_functions.empty())
		{
			output << "Empty" << std::endl;
			return { Status::OK };
		}
		FunctionEvalution(mapValueFunctions);

		for (auto it = mapValueFunctions.begin(); it != mapValueFunctions.end(); ++it)
		{
			output << it->first << "=" << it->second << std::endl;
		}
		return { Status::OK };
	}

	Result Calculator::ExecutePrintAllVariables(std::ostream & output) const
	{
		if (m_variables.empty())
		{
			output << "Empty" << std::endl;
			return { Status::OK };
		}
		for (auto it = m_variables.cbegin(); it != m_variables.cend(); ++it)
		{
			output << it->first << "=" << it->second << "\n";
		}
		return { Status::OK };
	}

	Result Calculator::FindValueFunctions(const char& ident, double firstNumber, double secondNumber, double& result)
	{
		Function::Operation operation;
		switch (ident)
		{
		case '+':
			operation = Function::Operation::ADD;
			break;
		case '-':
			operation = Function::Operation::SUB;
			break;
		case '*':
			operation = Function::Operation::MUL;
			break;
		case '/':
			operation = Function::Operation::DIV;
			break;
		default:
			return { Status::ERROR, "Internal error: unknown function operation recieved." };
		}
		result = m_function.CalculateValue(firstNumber, secondNumber, operation);
		return { Status::OK };
	}