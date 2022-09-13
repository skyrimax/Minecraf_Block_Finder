#include "CSVOutput.h"

#include <string>

#include "Utility.h"

CSVOutput::CSVOutput(int id, int dim,
	std::string separator)
	: AbstractOutput{id, dim}, m_separator{ separator },
	CSVFile{}
{
	update();
}

CSVOutput::~CSVOutput()
{
	CSVFile.close();
}

void CSVOutput::setSeparator(std::string separator)
{
	m_separator = separator;
}

void CSVOutput::print(int x, int y, int z)
{
	if (!CSVFile.is_open()) {
		CSVFile << x << m_separator << z << m_separator << y << std::endl;
	}
}

void CSVOutput::update()
{
	CSVFile.close();

	std::string path = getCSVfileName();

	CSVFile.open(path, std::ios::in | std::ios::out | std::ios::app);

	if (is_empty(path)) {
		CSVFile << "sep=" << m_separator << std::endl
				<< "x" << m_separator << "z" << m_separator << "y" << std::endl;
	}
}

std::string CSVOutput::getCSVfileName()
{
	struct tm dateTime;
	localtime_s(&dateTime, &AbstractOutput::startupTime);

	std::stringstream m_CSVfileName;

	m_CSVfileName << "Block_" << m_id << "_Dimension_" << m_dim << "_"
		<< (dateTime.tm_year + 1900) << "_" << (dateTime.tm_mon + 1) << "_" << (dateTime.tm_mday) << "_"
		<< dateTime.tm_hour << "_" << dateTime.tm_min << "_" << dateTime.tm_sec << ".csv";

	return m_CSVfileName.str();
}