#pragma once

#include <filesystem>
#include <vector>

#include <future>

#include "Coordinate.hpp"

class RegionBlockFinder
{
public:
	RegionBlockFinder(std::filesystem::path path = "C:\\world",
		int dim = 0, int regionX = 0, int regionZ = 0, int id = 1, bool multythreaded = false) :
		m_path { path }, m_dim { dim }, m_regionX { regionX }, m_regionZ { regionZ },
		m_id{ id }, m_multythreaded{ multythreaded }
	{

	}


	void setRegion(int regionX = 0, int regionZ = 0);

	std::vector<Coordinate> Search();

private:
	std::vector<Coordinate> searchSingleThread();
	std::vector<Coordinate> searchMultyThread();

	std::vector<Coordinate> workerSingleThread(size_t chunkX, size_t chunkZ, size_t section);
	void worker(std::promise<std::vector<Coordinate>>& blocksInSection, size_t chunkX, size_t chunkZ, size_t section);

	std::filesystem::path m_path;
	int m_dim;
	int m_regionX;
	int m_regionZ;
	int m_id;
	bool m_multythreaded;
};

