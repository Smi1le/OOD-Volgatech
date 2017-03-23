#include "stdafx.h"
#include "Circle.h"


float CCircle::GetPerimeter()
{
	return static_cast<float>(2 * M_PI * m_radius);
}

float CCircle::GetArea()
{
	return static_cast<float>(M_PI * (m_radius * m_radius));
}

