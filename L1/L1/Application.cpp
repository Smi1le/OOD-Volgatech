#include "stdafx.h"
#include "Application.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"

namespace calc
{
	float GetLengthSegment(std::pair<float, float> firstPoint, std::pair<float, float> secondPoint)
	{
		return std::sqrt(std::pow(secondPoint.first - firstPoint.first, 2) + std::pow(secondPoint.second - firstPoint.second, 2));
	}

	std::pair<std::string, std::string> GetCoordinatePoint(std::string const &point)
	{
		size_t pos = point.find(',');
		return { point.substr(0, pos), point.substr(pos + 1) };
	}


}

CApplication::CApplication(std::string const & fileName, std::string const &outFile)
{
	m_iomanager = CIOManager(fileName, outFile);
	if (!m_iomanager.ReadDataFromFile(m_dataBeforeParser))
	{
		throw std::runtime_error("file not found");
	}
	m_dataAfterParser = Parse();
}

void CApplication::OutputResults()
{
	std::vector<std::string> outputData;
	for (auto element : m_dataAfterParser)
	{
		outputData.push_back(this->GetOutputLine(element));
	}
	m_iomanager.OutputDataFromFile(outputData);
	m_iomanager.OutputDataFromConsole(outputData);
}

std::vector<std::shared_ptr<CShape>> CApplication::Parse()
{
	std::vector<std::shared_ptr<CShape>> records;
	for (auto element : m_dataBeforeParser)
	{
		std::vector<std::string> listValues;
		auto it = element.find(':');
		std::string type = element.substr(0, it);
		listValues.push_back(type);
		element = element.substr(it + 1);
		
		if (type == "CIRCLE")
		{
			it = element.find_last_of('R');
			listValues.push_back(element.substr(it + 2));
		}
		else 
		{
			std::vector<std::string> namesList;
			size_t numberPoints;
			if (type == "TRIANGLE")
			{
				namesList = { "P1", "P2", "P3" };
				numberPoints = 3;
			}
			else if (type == "RECTANGLE")
			{
				namesList = { "P1", "P2" };
				numberPoints = 2;
			}

			for (size_t i = 0; i != numberPoints; ++i)
			{
				it = element.find(namesList.at(i));
				auto it2 = element.find(";");
				auto point = calc::GetCoordinatePoint(element.substr(it + 3, it2 - it - 3));
				listValues.push_back(point.first);
				listValues.push_back(point.second);
				if (i < numberPoints - 1)
				{
					element = element.substr(it2 + 1);
				}
			}
		}
		records.push_back(GetNewRecord(listValues));
	}

	return records;
}

std::shared_ptr<CShape> CApplication::GetNewRecord(std::vector<std::string> const & data)
{
	std::shared_ptr<CShape> shape = std::make_unique<CShape>();
	if (data.at(0) == "RECTANGLE")
	{
		std::pair<float, float> firstPoint = { (float)atof(data[1].c_str()), (float)atof(data[2].c_str()) };
		std::pair<float, float> secondPoint = { (float)atof(data[1].c_str()), (float)atof(data[4].c_str()) };
		std::pair<float, float> thirdPoint = { (float)atof(data[3].c_str()), (float)atof(data[4].c_str()) };

		shape = std::move(std::make_shared<CRectangle>("RECTANGLE", calc::GetLengthSegment(firstPoint, secondPoint), calc::GetLengthSegment(secondPoint, thirdPoint)));
	}
	else if (data.at(0) == "CIRCLE")
	{
		shape = std::move(std::make_shared<CCircle>("CIRCLE", (float)atof(data[1].c_str())));
	}
	else if (data.at(0) == "TRIANGLE")
	{
		std::pair<float, float> firstPoint = { (float)atof(data[1].c_str()), (float)atof(data[2].c_str()) };
		std::pair<float, float> secondPoint = { (float)atof(data[3].c_str()), (float)atof(data[4].c_str()) };
		std::pair<float, float> thirdPoint = { (float)atof(data[5].c_str()), (float)atof(data[6].c_str()) };

		shape = std::move(std::make_shared<CRectangle>("TRIANGLE", calc::GetLengthSegment(firstPoint, secondPoint), calc::GetLengthSegment(secondPoint, thirdPoint)));
	}

	return shape;
}

std::string CApplication::GetOutputLine(std::shared_ptr<CShape> shape)
{
	return shape->GetType() + ": P=" + std::to_string(shape->GetPerimeter()) + ": S=" + std::to_string(shape->GetArea());
}
