#include "DataExtractor.hpp"

#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

std::vector<std::vector<std::vector<int>>> DataExtractor::extractChunk(std::filesystem::path pathToRegion, int chunkX, int chunkZ)
{
	loadChunkDataFromWorld(pathToRegion, chunkX, chunkZ);
	return parseChunkDataFromWorld(pathToRegion, chunkX, chunkZ);
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

std::string DataExtractor::chunkDataFilename(std::filesystem::path regionFile, size_t chunkX, size_t chunkZ)
{
	std::stringstream filename;

	std::string regionCoordinate = regionFile.filename().replace_extension("").string().substr(2);

	std::string dim;

	if((regionFile.end()-- -- --)->string().find("DIM")!= std::string::npos)
		dim = (regionFile.end()-- -- --)->string();
	else
		dim = "DIM0";

	filename << dim << "." << regionCoordinate << "." << chunkX << "." << chunkZ << ".json";

	return filename.str();
}