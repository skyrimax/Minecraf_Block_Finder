#include "ConsoleOutput.h"

#include <iostream>

void ConsoleOutput::print(int x, int y, int z)
{
	std::cout << "Found block id " << m_id <<
		" at x: " << x << " z: " << z << " y: " << z <<
		"in dimension " << m_dim << std::endl;
}

ConsoleOutput::ConsoleOutput(int id, int dim)
	: AbstractOutput{id, dim}
{
}

ConsoleOutput::~ConsoleOutput()
{
}

void ConsoleOutput::update()
{
}
