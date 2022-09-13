#include "DataExtractor.h"

#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

std::vector<std::vector<std::vector<int>>> DataExtractor::extractChunk(std::filesystem::path pathToRegion, int chunkX, int chunkZ)
{
	loadChunkDataFromWorld(pathToRegion, chunkX, chunkZ);
	return parseChunkDataFromWorld(pathToRegion, chunkX, chunkZ);
}

std::vector<DataExtractor::chunkParams> DataExtractor::extractChunksParamsFromWorld(std::filesystem::path pathToDim, int regionX, int regionZ)
{
	std::vector<chunkParams> chunksParams;
	chunksParams.reserve(m_nbChunksInRegion);
	chunkParams currentChunk;

	for (int x = 0; x < m_nbChunksInRegionX; ++x) {
		for (int z = 0; z < m_nbChunksInRegionZ; ++z) {
			if (!testIfChunkExist(pathToDim, regionX, regionZ, x, z))
				continue;

			int y = 1;
			int prevY = 0;

			while (1) {
				if (!testIfSectionExist(pathToDim, regionX, regionZ, x, z, y) || prevY == m_maxSectionY) {
					currentChunk.x = x;
					currentChunk.z = z;
					currentChunk.nbSections = prevY;

					chunksParams.push_back(currentChunk);

					break;
				}

				prevY = y;
				++y;
			}
		}
	}

	return chunksParams;
}

std::vector<int> DataExtractor::extractSectionDataFromWorld(std::filesystem::path pathToDim, int regionX, int regionZ, size_t chunkX, size_t chunkZ, size_t sectionY)
{
	loadSectionDataFromWorld(pathToDim, regionX, regionZ, chunkX, chunkZ, sectionY);
	return parseSectionDataFromWorld(regionX, regionZ, chunkX, chunkZ, sectionY);
}

void DataExtractor::loadChunkDataFromWorld(std::filesystem::path pathToRegion, size_t chunkX, size_t chunkZ)
{
	std::stringstream command;

	std::string filename = chunkDataFilename(pathToRegion, chunkX, chunkZ);

	command << "NBTUtil.exe --path \"" << pathToRegion << "\\" << chunkX << "." << chunkZ << "\\Level\\Sections --json \"" << filename << "\"";

	system(command.str().c_str());
}

std::vector<std::vector<std::vector<int>>> DataExtractor::parseChunkDataFromWorld(std::filesystem::path pathToRegion, size_t chunkX, size_t chunkZ)
{
	std::ifstream f(chunkDataFilename(pathToRegion, chunkX, chunkZ));
	nlohmann::json chunkData = nlohmann::json::parse(f);
	std::vector<std::vector<std::vector<int>>> chunk(16, std::vector<std::vector<int>>(256, std::vector<int>(16)));

	for (const auto& sectionData : chunkData) {
		std::vector<int> blocks;

		int y = sectionData["y"];
		blocks.insert(blocks.end(), sectionData["Blocks"].begin(), sectionData["Blocks"].end());

		for (size_t i = 0; i < blocks.size(); ++i) {
			int sectionX = i % 16;
			int sectionZ = (i / 16) % 16;
			int sectionY = (i / 256) % 16 + 16 * y;

			chunk[sectionX][sectionY][sectionZ] = blocks[i];
		}
	}

	return chunk;
}

void DataExtractor::loadSectionDataFromWorld(std::filesystem::path pathToDim, int regionX, int regionZ, size_t chunkX, size_t chunkZ, size_t sectionY)
{
	std::stringstream command;

	std::string filename = sectionDataFileName(regionX, regionZ, chunkX, chunkZ, sectionY);

	command << "NBTUtil.exe --path \"" << pathToDim.string() << "\\region\\r." << regionX << "." << regionZ << ".mca\\"
		<< chunkX << "." << chunkZ << "\\Level\\Sections\\" << sectionY << "\\Blocks\" --json \"" << filename << "\"";

	system(command.str().c_str());
}

std::vector<int> DataExtractor::parseSectionDataFromWorld(int regionX, int regionZ, size_t chunkX, size_t chunkZ, size_t sectionY)
{
	std::string filename = sectionDataFileName(regionX, regionZ, chunkX, chunkZ, sectionY);
	std::ifstream file(filename);

	std::vector<int> data;

	int id;

	if (!file.is_open()) {
		std::stringstream error;

		error << "Unable to open file " << filename;
		throw std::exception(error.str().c_str());
	}

	file.ignore(2);

	while (file.peek() != std::char_traits<char>::eof())
	{
		file >> id;

		data.push_back(id);

		file.ignore(2);
	}

	file.close();

	std::filesystem::remove(filename);

	return data;
}

void DataExtractor::loadSectionYDataFromWorld(std::filesystem::path pathToDim, int regionX, int regionZ, size_t chunkX, size_t chunkZ, size_t sectionY)
{
	std::stringstream command;

	std::string filename = sectionDataFileName(regionX, regionZ, chunkX, chunkZ, sectionY);

	command << "NBTUtil.exe --path \"" << pathToDim.string() << "\\region\\r." << regionX << "." << regionZ << ".mca\\"
		<< chunkX << "." << chunkZ << "\\Level\\Sections\\" << sectionY << "\\Y\" --json \"" << filename << "\"";

	system(command.str().c_str());
}

bool DataExtractor::testIfSectionExist(std::filesystem::path pathToDim, int regionX, int regionZ, size_t chunkX, size_t chunkZ, size_t sectionY)
{
	loadSectionYDataFromWorld(pathToDim, regionX, regionZ, chunkX, chunkZ, sectionY);

	std::string filename = sectionDataFileName(regionX, regionZ, chunkX, chunkZ, sectionY);

	if (std::filesystem::exists(filename)) {
		std::filesystem::remove(filename);

		return true;
	}

	return false;
}

bool DataExtractor::testIfChunkExist(std::filesystem::path pathToDim, int regionX, int regionZ, size_t chunkX, size_t chunkZ)
{
	loadSectionYDataFromWorld(pathToDim, regionX, regionZ, chunkX, chunkZ, 0);

	std::string filename = sectionDataFileName(regionX, regionZ, chunkX, chunkZ, 0);

	if (std::filesystem::exists(filename)) {
		std::filesystem::remove(filename);

		return true;
	}

	return false;
}

std::string DataExtractor::sectionDataFileName(int regionX, int regionZ, size_t chunkX, size_t chunkZ, size_t sectionY)
{
	std::stringstream filename;

	filename << regionX << "." << regionZ << "." << chunkX << "." << chunkZ << "." << sectionY << ".data.json";

	return filename.str();
}
