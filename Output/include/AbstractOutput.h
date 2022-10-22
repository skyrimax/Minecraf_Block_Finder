#pragma once

#include <ctime>
#include <vector>

class AbstractOutput
{
public:
	int getDim();
	virtual void setDim(int dim);

	int getID();
	virtual void setID(int id);

	virtual void print(int x, int y, int z) = 0;

protected:
	AbstractOutput(int id = 0, int dim = 0);

	virtual void update() = 0;

	int m_id;
	int m_dim;
	inline static const time_t startupTime = time(0);

	friend class Output;
};

