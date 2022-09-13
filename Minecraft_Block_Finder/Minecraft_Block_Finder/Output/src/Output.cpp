#include "Output.h"

#include "ConsoleOutput.h"
#include "CSVOutput.h"

Output::Output(OutputType output_type,
	int id, int dim)
	: AbstractOutput{id, dim}
{
	if ((output_type & OutputType::Console) == OutputType::Console) {
		m_instanciated_objects.push_back(std::move(std::unique_ptr<AbstractOutput>(new ConsoleOutput(id, dim))));
		//m_instanciated_objects.push_back(std::make_unique<ConsoleOutput>(id, dim));
	}

	if ((output_type & OutputType::CSV) == OutputType::CSV) {
		m_instanciated_objects.push_back(std::move(std::unique_ptr<AbstractOutput>(new CSVOutput(id, dim))));
		//m_instanciated_objects.push_back(std::make_unique<CSVOutput>(id, dim));
	}
}

void Output::setDim(int dim)
{
	for (auto& output : m_instanciated_objects) {
		output->setDim(dim);
	}

	update();
}

void Output::setID(int id)
{
	for (auto& output : m_instanciated_objects) {
		output->setID(id);
	}

	update();
}

void Output::print(int x, int y, int z)
{
	for (auto& output : m_instanciated_objects) {
		output->print(x, y, z);
	}
}

void Output::update()
{
	for (auto& output : m_instanciated_objects) {
		output->update();
	}
}
