#pragma once


class CTriangle : public CShape
{
public:
	CTriangle(std::string const & type, float lengthA, float lengthB, float lengthC)
		: CShape(type)
		, m_lengthA(lengthA)
		, m_lengthB(lengthB)
		, m_lengthC(lengthC)
	{}

	float GetPerimeter() override;
	float GetArea() override;
private:
	float m_lengthA;
	float m_lengthB;
	float m_lengthC;
};
