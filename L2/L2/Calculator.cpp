#include "stdafx.h"
#include "Calculator.h"

void CCalculator::AddExpression(std::string const & expression)
{
	std::stringstream ss(expression);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> stringDict(begin, end);
	SExpression expr;

	expr.firstArg = CLongValue(stringDict.at(0));
	std::string op = stringDict.at(1);
	expr.typeOperand = op == "+" ? TypeOperand::ADDITION: op == "-" ? TypeOperand::SUBTRACTION: op == "/" ? 
		TypeOperand::DIVISION : op == "*" ? TypeOperand::MULTIPLICATION : TypeOperand::ADDITION;
	expr.secondArg = CLongValue(stringDict.at(2));
	m_expressions.push_back(expr);
}

void CCalculator::CountAll()
{
	for (auto &el : m_expressions)
	{
		switch (el.typeOperand)
	{	
		case TypeOperand::ADDITION:
			el.result = el.firstArg + el.secondArg;
			break;
		case TypeOperand::DIVISION:
			el.result = el.firstArg / el.secondArg;
			break;
		case TypeOperand::MULTIPLICATION:
			el.result = el.firstArg * el.secondArg;
			break;
		case TypeOperand::SUBTRACTION:
			el.result = el.firstArg - el.secondArg;
			break;
		}
	}
}

void CCalculator::OutputResults()
{
	for (auto el : m_expressions)
	{
		el.result.Output();
	}
}
