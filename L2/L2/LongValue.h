#pragma once


enum class TypeOperand {
	ADDITION,
	MULTIPLICATION,
	DIVISION,
	SUBTRACTION
};


class CLongValue {
public:
	CLongValue() = default;
	CLongValue(std::string const &value);
	void SetLength(size_t length);
	size_t GetLength() const;
	CLongValue const operator+(CLongValue const &rhs);
	CLongValue const operator-(CLongValue const &rhs);
	CLongValue const operator*(CLongValue const &rhs);
	CLongValue const operator/(CLongValue rhs);
	friend bool const operator<(CLongValue const &lhs, CLongValue const &rhs);
	friend bool const operator>(CLongValue lhs, CLongValue rhs);
	void Output();
private:
	std::vector<int> GetSubVector(size_t startPos, size_t count);
	void ParseInputValue(std::string const &value);
	void BuildUpVector(size_t count);
	CLongValue GetNewLongValue(CLongValue const &value);
	CLongValue GetResultCalculationWork(CLongValue const &rhs, TypeOperand type);
	void Normalize(CLongValue &value);
private:
	size_t m_length;
	std::vector<int> m_values;
};