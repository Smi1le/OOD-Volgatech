#pragma once


class CCircle : public CShape
{
public:
	CCircle(std::string const & type, float radius)
		: CShape(type)
		, m_radius(radius)
	{}

	float GetPerimeter() override;
	float GetArea() override;
private:
	float m_radius;
};