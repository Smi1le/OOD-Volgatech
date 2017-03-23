#include "stdafx.h"
#include "IOManager.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>





CIOManager::CIOManager(std::string const & inF, std::string const & outF)
	: m_inputFile(inF)
	, m_outputFile(outF)
{
}

bool CIOManager::ReadDataFromFile(std::vector<std::string> &data)
{
	std::ifstream file(m_inputFile);
	if (!file)
	{
		std::cerr << "File not found" << std::endl;
		return false;
	}
	std::string value;
	
	while (std::getline(file, value))
	{
		data.push_back(value);
	}
	return true;
}

void CIOManager::OutputDataFromConsole(std::vector<std::string> const &data)
{
	for (auto const &element : data)
	{
		std::cout << element << std::endl;
	}
}

void CIOManager::OutputDataFromFile(std::vector<std::string> const &data)
{
	std::ofstream file(m_outputFile);

	for (auto const &element : data)
	{
		file << element << '\n';
	}
}
