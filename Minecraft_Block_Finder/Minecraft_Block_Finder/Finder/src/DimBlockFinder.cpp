#include "DimBlockFinder.h"

#include <sstream>

#include "RegionBlockFinder.h"

void DimBlockFinder::setDim(int dim)
{
	m_dim = dim;

	m_output.setDim(dim);
}

void DimBlockFinder::Search()
{
	std::vector<Coordinate> blocks(0);

	if (m_multythreaded) {
		blocks = searchMultyThread();
	}
	else {
		blocks = searchSingleThread();
	}

	for (const auto& block : blocks) {
		m_output.print(block.x, block.y, block.z);
	}
}

std::vector<Coordinate> DimBlockFinder::searchSingleThread()
{
	int regionX;
	int regionZ;

	RegionBlockFinder regionBlockFinder(m_path, m_dim, 0, 0, m_id, m_multythreaded);

	std::vector<Coordinate> blocksInDim;
	std::vector<Coordinate> blocksInRegion;

	std::filesystem::path pathToDim = m_path.string() + std::string("\\")
		+ (m_dim ? std::string("DIM") + std::to_string(m_dim) + std::string("\\") : std::string(""))
		+ std::string("region");

	for (const auto& region : std::filesystem::directory_iterator(pathToDim)) {
		if (region.path().extension().string() == std::string(".mca"))
		{
			std::stringstream file(region.path().filename().string());

			file.ignore(2);

			file >> regionX;

			file.ignore();

			file >> regionZ;

			regionBlockFinder.setRegion(regionX, regionZ);

			blocksInRegion = regionBlockFinder.Search();

			blocksInDim.insert(std::end(blocksInDim), std::begin(blocksInRegion), std::end(blocksInRegion));
		}
	}

	return blocksInDim;
}

std::vector<Coordinate> DimBlockFinder::searchMultyThread()
{
	int regionX;
	int regionZ;

	std::vector<Coordinate> blocksInDim;

	std::vector<RegionCoordinate> regions;

	std::filesystem::path pathToDim = m_path.string() + std::string("\\")
		+ (m_dim ? std::string("DIM") + std::to_string(m_dim) + std::string("\\") : std::string(""))
		+ std::string("region");

	for (const auto& region : std::filesystem::directory_iterator(pathToDim)) {
		if (region.path().extension().string() == std::string(".mca"))
		{
			std::stringstream file(region.path().filename().string());

			file.ignore(2);

			file >> regionX;

			file.ignore();

			file >> regionZ;

			regions.push_back(RegionCoordinate(regionX, regionZ));
		}
	}

	std::vector<std::promise<std::vector<Coordinate>>> returnBlocksInRegions(regions.size());

	std::vector<std::future<std::vector<Coordinate>>> blocksInRegions;

	std::vector<std::thread> threads;

	for (size_t indexThread = 0; indexThread < regions.size(); ++indexThread) {
		blocksInRegions.push_back(returnBlocksInRegions[indexThread].get_future());

		threads.push_back(std::thread(&DimBlockFinder::worker, this,
			std::ref(returnBlocksInRegions[indexThread]), regions[indexThread].regionX, regions[indexThread].regionZ));
	}

	for (auto& thread : threads) {
		thread.join();
	}

	for (auto& blocksInRegion : blocksInRegions) {
		blocksInDim.insert(std::end(blocksInDim), std::begin(blocksInRegion.get()), std::end(blocksInRegion.get()));
	}

	return blocksInDim;
}

void DimBlockFinder::worker(std::promise<std::vector<Coordinate>>& blocksInRegion, int regionX, int regionZ)
{
	RegionBlockFinder regionBlockFinder(m_path, m_dim, regionX, regionZ, m_id, m_multythreaded);

	blocksInRegion.set_value_at_thread_exit(regionBlockFinder.Search());
}
