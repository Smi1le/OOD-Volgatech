#pragma once




class CRectangle : public CShape
{
public:
	CRectangle(std::string const & type, float lengthA, float lengthB)
		: CShape(type)
		, m_lengthA(lengthA)
		, m_lengthB(lengthB)
	{}

	float GetPerimeter() override;
	float GetArea() override;
private:
	float m_lengthA;
	float m_lengthB;
};