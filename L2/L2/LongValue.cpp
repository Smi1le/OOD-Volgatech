#include "stdafx.h"
#include "LongValue.h"

using namespace std;

CLongValue::CLongValue(std::string const & value)
	: m_length(value.size())

{
	ParseInputValue(value);
}


void CLongValue::Output()
{
	std::reverse(m_values.begin(), m_values.end());
	for (int el : m_values)
	{
		std::cout << el;
	}
	std::cout << std::endl;
}

std::vector<int> CLongValue::GetSubVector(size_t startPos, size_t count)
{
	try
	{
		if (startPos - count > m_values.size())
		{
			throw std::range_error("position is out of range");
		}
		std::vector<int> subVector;
		subVector.reserve(count);
		for (size_t i = startPos; i != startPos - count; --i)
		{
			subVector.push_back(m_values.at(i));
		}
		return subVector;
	}
	catch (std::range_error const &ex)
	{
		throw ex;
	}
}

void CLongValue::ParseInputValue(std::string const &value)
{
	for (auto element : value)
	{
		m_values.push_back((static_cast<int>(element) - 48));
	}
	std::reverse(m_values.begin(), m_values.end());
}

void CLongValue::BuildUpVector(size_t count)
{
	while (this->m_values.size() != count)
	{
		this->m_values.push_back(0);
	}
	this->m_length = this->m_values.size();
}

CLongValue const CLongValue::operator+(CLongValue const & rhs)
{
	return GetResultCalculationWork(rhs, TypeOperand::ADDITION);
}

CLongValue const CLongValue::operator-(CLongValue const & rhs)
{
	return GetResultCalculationWork(rhs, TypeOperand::SUBTRACTION);
}

CLongValue const CLongValue::operator*(CLongValue const & rhs)
{
	CLongValue result;
	result.m_length = m_length + rhs.m_length + 1;
	result.m_values.resize(result.m_length);
	for (size_t i = 0; i < m_length; ++i)
	{
		for (size_t j = 0; j < rhs.m_length; ++j)
		{
			result.m_values.at(i + j) += m_values.at(i) * rhs.m_values.at(j);
		}
	}

	for (size_t i = 0; i < result.m_length; ++i)
	{
		if (i + 1 == result.m_length)
		{
			continue;
		}
		result.m_values.at(i + 1) += result.m_values.at(i) / 10;
		result.m_values.at(i) %= 10;
	}
	Normalize(result);
	return result;
}

CLongValue const CLongValue::operator/(CLongValue rhs)
{
	CLongValue value;
	CLongValue copyLhs = *this;
	int innerCount = copyLhs.m_length - 1;
	CLongValue intermediateValue;
	intermediateValue.m_values = copyLhs.GetSubVector(innerCount, rhs.m_values.size());
	std::reverse(intermediateValue.m_values.begin(), intermediateValue.m_values.end());
	intermediateValue.m_length = intermediateValue.m_values.size();
	while (true)
	{
		if (copyLhs.m_values.size() < rhs.m_values.size())
		{
			return value;
		}
		int k = 1;
		while (intermediateValue < rhs)
		{
			try
			{
				intermediateValue.m_values = copyLhs.GetSubVector(innerCount, intermediateValue.m_values.size() + k);
				std::reverse(intermediateValue.m_values.begin(), intermediateValue.m_values.end());
				intermediateValue.m_length = intermediateValue.m_values.size();
				++k;
			}
			catch (std::range_error)
			{
				Normalize(value);
				return value;
			}
		}
		int count = 0;
		while (true) {
			if (intermediateValue - rhs < CLongValue("0"))
			{
				break;
			}
			intermediateValue = intermediateValue - rhs;
			++count;
		}
		value.m_values.insert(value.m_values.begin(), count);
		value.m_length = value.m_values.size();

		try 
		{
			auto newValue = copyLhs.GetSubVector(innerCount-- - rhs.m_values.size() + 1, 1).at(0);
			intermediateValue.m_values.insert(intermediateValue.m_values.begin(), newValue);
			intermediateValue.m_length = intermediateValue.m_values.size();
		}
		catch (std::range_error)
		{
			return value;
		}
	}
	return nullptr;
}


CLongValue CLongValue::GetNewLongValue(CLongValue const &value)
{
	CLongValue result;
	result.m_length = value.m_length;
	result.m_values.resize(result.m_length);
	return result;
}

CLongValue CLongValue::GetResultCalculationWork(CLongValue const &rhs, TypeOperand type)
{
	CLongValue lhs = *this;
	bool isFirstValueBiggestThanSecond = rhs.m_length < lhs.m_length;
	CLongValue result = GetNewLongValue(isFirstValueBiggestThanSecond ? lhs : rhs);

	if (lhs.m_values.size() < rhs.m_values.size())
	{
		lhs.BuildUpVector(rhs.m_values.size());
	}

	for (size_t i = 0; i < (isFirstValueBiggestThanSecond ? lhs : rhs).m_length; ++i)
	{
		if (i < lhs.m_length && i < rhs.m_length)
		{
			switch (type)
			{
			case TypeOperand::ADDITION:
				result.m_values.at(i) = lhs.m_values.at(i) + rhs.m_values.at(i);
				break;
			case TypeOperand::SUBTRACTION:
				result.m_values.at(i) = lhs.m_values.at(i) - rhs.m_values.at(i);
				break;
			}
			
		}
		else if (i >= lhs.m_length)
		{
			result.m_values.at(i) = rhs.m_values.at(i);
		}
		else {
			result.m_values.at(i) = lhs.m_values.at(i);
		}
	}
	Normalize(result);
	return result;
}

void CLongValue::Normalize(CLongValue &value)
{
	while (true)
	{
		for (size_t i = 0; i != value.m_length; ++i)
		{
			if (value.m_values.at(i) < 0)
			{
				if (i + 1 == value.m_length)
				{
					break;
				}
				value.m_values.at(i + 1) -= 1;
				value.m_values.at(i) += 10;
			}
			else if (value.m_values.at(i) > 9)
			{
				if (i + 1 == value.m_length)
				{
					break;
				}
				value.m_values.at(i + 1) += 1;
				value.m_values.at(i) -= 10;
			}
		}
		if (value.m_values.at(value.m_values.size() - 1) < 0)
		{
			break;
		}
		int innerCount = 0;
		for (int el : value.m_values)
		{
			if (el < 0)
			{
				break;
			}
			++innerCount;
		}
		if (innerCount == value.m_length)
		{
			break;
		}
	}
	for (size_t i = value.m_length - 1; i != -1; --i)
	{
		if (value.m_values.at(i) == 0)
		{
			value.m_values.pop_back();
			value.m_length -= 1;
		}
		else
		{
			break;
		}
	}
}

void CLongValue::SetLength(size_t length)
{
	m_length = length;
}

size_t CLongValue::GetLength() const
{
	return m_length;
}


bool const operator<(CLongValue const & lhs, CLongValue const & rhs)
{
	return !(lhs > rhs);
}

bool const operator>(CLongValue lhs, CLongValue rhs)
{

	if (lhs.m_values.size() < rhs.m_values.size())
	{
		lhs.BuildUpVector(rhs.m_values.size());
	}
	else if (lhs.m_values.size() > rhs.m_values.size()) {
		rhs.BuildUpVector(lhs.m_values.size());
	}
	for (int innerCount = lhs.m_values.size() - 1; innerCount != -1; --innerCount)
	{
		if (lhs.m_values.at(innerCount) == rhs.m_values.at(innerCount))
		{
			continue;
		}
		else if (lhs.m_values.at(innerCount) > rhs.m_values.at(innerCount))
		{
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}