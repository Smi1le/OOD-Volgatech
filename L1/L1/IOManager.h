#pragma once




class CIOManager
{
public:
	CIOManager() = default;
	CIOManager(std::string const &inF, std::string const &outF);
	bool ReadDataFromFile(std::vector<std::string> &data);
	void OutputDataFromConsole(std::vector<std::string> const &data);
	void OutputDataFromFile(std::vector<std::string> const &data);
private:
	std::string m_inputFile;
	std::string m_outputFile;
};