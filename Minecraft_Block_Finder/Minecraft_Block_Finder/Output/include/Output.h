#pragma once
#include "AbstractOutput.h"

#include <type_traits>
#include <memory>

class Output :
	public AbstractOutput
{
public:

	enum class OutputType : int8_t
	{
		Console = 1 << 0,
		CSV = 1 << 1
	};

	Output(OutputType output_type = OutputType(0),
		int id = 0, int dim = 0);

	virtual void setDim(int dim) override;

	virtual void setID(int id) override;

	virtual void print(int x, int y, int z) override;

protected:
	virtual void update();

	std::vector<std::unique_ptr<AbstractOutput>> m_instanciated_objects;
};

inline Output::OutputType operator| (Output::OutputType lhs, Output::OutputType rhs) {
		using T = std::underlying_type_t<Output::OutputType>;
		return static_cast<Output::OutputType>(static_cast<T>(lhs) | static_cast<T>(rhs));
	}

inline Output::OutputType& operator|= (Output::OutputType& lhs, Output::OutputType rhs) {
	lhs = lhs | rhs;
	return lhs;
}

inline Output::OutputType operator& (Output::OutputType lhs, Output::OutputType rhs) {
	using T = std::underlying_type_t<Output::OutputType>;
	return static_cast<Output::OutputType>(static_cast<T>(lhs) & static_cast<T>(rhs));
}

inline Output::OutputType& operator&= (Output::OutputType& lhs, Output::OutputType rhs) {
	lhs = lhs & rhs;
	return lhs;
}