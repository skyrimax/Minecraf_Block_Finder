#pragma once

#include "AbstractOutput.h"

#include <memory>
#include <fstream>
#include <sstream>
#include <filesystem>

class CSVOutput : public AbstractOutput
{
public:
	~CSVOutput();

	void setSeparator(std::string separator);

	virtual void print(int x, int y, int z) override;

	CSVOutput(int id = 0, int dim = 0,
		std::string separator = ",");

protected:
	//CSVOutput(int id = 0, int dim = 0,
	//	std::string separator = ",");

	virtual void update();

	std::string m_separator;
	std::fstream CSVFile;

	std::string getCSVfileName();

	friend class output;
	friend class std::unique_ptr<CSVOutput>;
};