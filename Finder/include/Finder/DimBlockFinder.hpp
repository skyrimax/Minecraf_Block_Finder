#pragma once

#include <filesystem>
#include <vector>

#include <future>

#include "thread_pool.hpp"

#include "Coordinate.hpp"

#include "Output.hpp"

class DimBlockFinder
{
public:
	DimBlockFinder(std::filesystem::path path = "C:\\world",
		int dim = 0, int id = 1, bool multythreaded = false,
		Output::OutputType outputType = Output::OutputType::CSV) :
		m_path{ path }, m_dim{ dim }, m_id{ id }, m_multythreaded{ multythreaded },
		m_output(outputType, id, dim)
	{

	}

	void setDim(int dim);

	void Search();

private:
	struct RegionCoordinate
	{
		RegionCoordinate() = default;
		RegionCoordinate(int regionX, int regionZ)
			: regionX{ regionX }, regionZ{ regionZ }
		{

		}
	
		int regionX;
		int regionZ;
	};

	std::vector<Coordinate> searchSingleThread();
	std::vector<Coordinate> searchMultyThread();

	void worker(std::promise<std::vector<Coordinate>>& blocksInRegion, int regionX, int regionZ);

	std::filesystem::path m_path;
	int m_dim;
	int m_id;
	bool m_multythreaded;

	Output m_output;
};

