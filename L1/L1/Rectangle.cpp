#include "stdafx.h"
#include "Rectangle.h"

float CRectangle::GetPerimeter()
{
	return m_lengthA * 2 + m_lengthB * 2;
}

float CRectangle::GetArea()
{
	return m_lengthA * m_lengthB;
}