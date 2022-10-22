#pragma once
#include "AbstractOutput.h"

#include <memory>

class ConsoleOutput :
	public AbstractOutput
{
public:
	~ConsoleOutput();

	virtual void print(int x, int y, int z) override;

	ConsoleOutput(int id = 0, int dim = 0);

protected:
	virtual void update();

	friend class output;
	friend class std::unique_ptr<ConsoleOutput>;
};