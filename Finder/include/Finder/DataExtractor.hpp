#pragma once

#include <vector>
#include <filesystem>
#include <string>

class DataExtractor
{
public:
	struct chunkParams
	{
		int x;
		int z;
		int nbSections;
	};

	static std::vector<std::vector<std::vector<int>>> extractChunk(std::filesystem::path pathToRegion,
		int chunkX, int chunkZ);

	static int maxSectionY() { return m_maxSectionY; }
	static int nbChunksInRegionX() { return m_nbChunksInRegionX; }
	static int nbChunksInRegionZ() { return m_nbChunksInRegionZ; }
	static int nbChunksInRegion() { return m_nbChunksInRegion; }

private:
	static void loadChunkDataFromWorld(std::filesystem::path pathToRegion, size_t chunkX, size_t chunkZ);
	static std::vector<std::vector<std::vector<int>>> parseChunkDataFromWorld(
		std::filesystem::path pathToRegion, size_t chunkX, size_t chunkZ);

	static std::string chunkDataFilename(std::filesystem::path regionFile, size_t chunkX, size_t chunkZ);

	inline static const int m_maxSectionY = 16;
	inline static const int m_nbChunksInRegionX = 32;
	inline static const int m_nbChunksInRegionZ = 32;
	inline static const int m_nbChunksInRegion = m_nbChunksInRegionX * m_nbChunksInRegionZ;
};

