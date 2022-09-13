#include "RegionBlockFinder.h"

#include <thread>

#include "DataExtractor.h"

void RegionBlockFinder::setRegion(int regionX, int regionZ)
{
	m_regionX = regionX;
	m_regionZ = regionZ;
}

std::vector<Coordinate> RegionBlockFinder::Search()
{
	if (m_multythreaded) {
		return searchMultyThread();
	}
	else {
		return searchSingleThread();
	}
}

std::vector<Coordinate> RegionBlockFinder::searchSingleThread()
{
	std::vector<Coordinate> blocksInRegion;
	std::vector<Coordinate> blocksInSection;

	for (size_t chunkX = 0; chunkX < DataExtractor::nbChunksInRegionX(); ++chunkX) {
		for (size_t chunkZ = 0; chunkZ < DataExtractor::nbChunksInRegionZ(); ++chunkZ) {
			for (size_t section = 0; section < DataExtractor::maxSectionY(); ++section) {
				blocksInSection = workerSingleThread(chunkX, chunkZ, section);

				blocksInRegion.insert(std::end(blocksInRegion), std::begin(blocksInSection), std::end(blocksInSection));
			}
		}
	}

	return blocksInRegion;
}

std::vector<Coordinate> RegionBlockFinder::searchMultyThread()
{
	std::vector<Coordinate> blocksInRegion;

	std::vector<std::promise<std::vector<Coordinate>>> returnBlocksInSections(
		DataExtractor::maxSectionY() * DataExtractor::nbChunksInRegion());

	std::vector<std::future<std::vector<Coordinate>>> blocksInSections;

	std::vector<std::thread> threads;

	for (size_t chunkX = 0, indexThread = 0; chunkX < DataExtractor::nbChunksInRegionX(); ++chunkX) {
		for (size_t chunkZ = 0; chunkZ < DataExtractor::nbChunksInRegionZ(); ++chunkZ) {
			for (size_t section = 0; section < DataExtractor::maxSectionY(); ++section, ++indexThread) {
				blocksInSections.push_back(returnBlocksInSections[indexThread].get_future());

				threads.push_back(std::thread(&RegionBlockFinder::worker, this,
					std::ref(returnBlocksInSections[indexThread]), chunkX, chunkZ, section));
			}
		}
	}

	for (auto& thread : threads) {
		thread.join();
	}

	for (auto& blocksInSection : blocksInSections) {
		blocksInRegion.insert(std::end(blocksInRegion), std::begin(blocksInSection.get()), std::end(blocksInSection.get()));
	}

	return blocksInRegion;
}

std::vector<Coordinate> RegionBlockFinder::workerSingleThread(size_t chunkX, size_t chunkZ, size_t section)
{
	std::vector<Coordinate> blocksInSection;
	std::vector<int> blocksData(DataExtractor::extractSectionDataFromWorld(
		m_path, m_regionX, m_regionZ, chunkX, chunkZ, section));

	size_t nbBlocks = blocksData.size();

	for (int index = 0; index < nbBlocks; ++index) {
		if (blocksData[index] = m_id) {
			int sectionX = index % 16;
			int sectionZ = (index / 16) % 16;
			int sectionY = (index / 256) % 16;

			blocksInSection.push_back(Coordinate(
				m_regionX * 512 + chunkX * 16 + sectionX,
				m_regionZ * 512 + chunkZ * 16 + sectionZ,
				section * 16 + sectionY + 1));
		}
	}

	return blocksInSection;
}

void RegionBlockFinder::worker(std::promise<std::vector<Coordinate>>& blocksInSection, size_t chunkX, size_t chunkZ, size_t section)
{
	blocksInSection.set_value_at_thread_exit(workerSingleThread(chunkX, chunkZ, section));
}
