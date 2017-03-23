#include "stdafx.h"
#include "Triangle.h"


float CTriangle::GetPerimeter()
{
	return m_lengthA + m_lengthB + m_lengthC;
}

float CTriangle::GetArea()
{
	float p = (this->GetPerimeter() / 2);
	return std::sqrt(p * (p - m_lengthA) * (p - m_lengthB) * (p - m_lengthC));
}
