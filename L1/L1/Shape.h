#pragma once

class CShape 
{
public:
	CShape() = default;
	CShape(std::string const &type)
		:m_type(type)
	{}
	virtual float GetPerimeter() { return 0.f; };
	virtual float GetArea() { return 0.f; };
	std::string GetType() const;

private:
	std::string m_type;
};
