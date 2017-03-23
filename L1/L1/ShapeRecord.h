#pragma once
#include <string>
#include <vector>


enum class Type
{
	Circle,
	Rectangle,
	Triangle
};

struct SShapeRecord
{
	Type type;
	std::vector<float> values;
};
