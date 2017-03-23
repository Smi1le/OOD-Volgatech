#pragma once
#include "Expression.h"



class CCalculator {
public:
	CCalculator() = default;
	void AddExpression(std::string const &expression);
	void CountAll();
	void OutputResults();
private:


private:
	std::vector<SExpression> m_expressions;
};