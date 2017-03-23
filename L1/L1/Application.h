#pragma once


class CApplication
{
public:
	CApplication(std::string const &fileName, std::string const &outFile);
	void OutputResults();

private:
	std::vector<std::shared_ptr<CShape>> Parse();
	std::shared_ptr<CShape> GetNewRecord(std::vector<std::string> const &data);
	std::string GetOutputLine(std::shared_ptr<CShape> shape);
private:
	CIOManager m_iomanager;
	std::vector<std::string> m_dataBeforeParser;
	std::vector<std::shared_ptr<CShape>> m_dataAfterParser;
};