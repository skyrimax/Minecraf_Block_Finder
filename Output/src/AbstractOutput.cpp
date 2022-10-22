#include "AbstractOutput.h"

AbstractOutput::AbstractOutput(int id, int dim)
	: m_id{ id }, m_dim{dim}
{
}

int AbstractOutput::getDim()
{
	return m_dim;
}

void AbstractOutput::setDim(int dim)
{
	m_dim = dim;

	//for (auto& instanciated_object : m_instanciated_objects) {
	//	instanciated_object->update();
	//}
}

int AbstractOutput::getID()
{
	return m_id;
}

void AbstractOutput::setID(int id)
{
	m_id = id;

	//for (auto& instanciated_object : m_instanciated_objects) {
	//	instanciated_object->update();
	//}
}
