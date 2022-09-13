#include "BlockFinder.h"

#include "DimBlockFinder.h"
#include "DataExtractor.h"

void BlockFinder::Search(const std::filesystem::path& pathToWorld,
	const std::vector<int>& dims, const std::vector<int>& id)
{
	std::map<int, std::map<int, std::vector<Coordinate>>> allMathces;

	auto loop = [this, pathToWorld, dims, id](const int a, const int b) {
		std::map<int, std::map<int, std::vector<Coordinate>>> matches;

		for (int i = a; i < b; ++i) {
			matches[dims[i]] = searchDim(pathToWorld, dims[i], id);
		}

		return matches;
	};

	auto matches = pool.parallelize_loop(0, dims.size(), loop);

	for (size_t i = 0; i < matches.f.size(); ++i) {
		while(matches.f[i].wait_for(std::chrono::microseconds(0)) != std::future_status::ready) {
			std::this_thread::yield();
		}

		allMathces.insert(matches.f[i].get().begin(), matches.f[i].get().end());
	}

	output(allMathces);
}

std::map<int, std::vector<Coordinate>> BlockFinder::searchDim(const std::filesystem::path& pathToWorld, int dim, std::vector<int> ids)
{
	auto dimDirectory = std::filesystem::directory_iterator(pathToDimData(pathToWorld, dim));
	std::vector<std::filesystem::path> regionFiles;
	std::map<int, std::vector<Coordinate>> allMatches;

	for (const auto& id : ids) {
		allMatches[id] = std::vector<Coordinate>();
	}

	for (const auto& file : dimDirectory) {
		std::filesystem::path filePath = file.path();
		if (filePath.extension() == ".mca") {
			regionFiles.push_back(filePath);
		}
	}

	auto loop = [this, regionFiles, ids](const int a, const int b) {
		std::map<int, std::vector<Coordinate>> matches;

		for (const auto& id : ids) {
			matches[id] = std::vector<Coordinate>();
		}

		for (int i = a; i < b; ++i) {
			auto res = searchRegion(regionFiles[i], ids);

			for (const auto& id : ids) {
				matches[id].insert(matches[id].end(), res[id].begin(), res[id].end());
			}
		}

		return matches;
	};

	auto matches = pool.parallelize_loop(0, regionFiles.size(), loop);

	for (size_t i = 0; i < matches.f.size(); ++i) {
		while (matches.f[i].wait_for(std::chrono::microseconds(0)) != std::future_status::ready) {
			std::this_thread::yield();
		}

		for (const auto& id : ids) {
			allMatches[id].insert(allMatches[id].end(), matches.f[i].get().begin(), matches.f[i].get().end());
		}
	}

	return allMatches;
}

std::map<int, std::vector<Coordinate>> BlockFinder::searchRegion(const std::filesystem::path & pathToRegion, const std::vector<int>& ids)
{
	std::map<int, std::vector<Coordinate>> allMatches;

	for (const auto& id : ids) {
		allMatches[id] = std::vector<Coordinate>();
	}

	auto loop = [this, pathToRegion, ids](const int a, const int b) {
		std::map<int, std::vector<Coordinate>> matches;

		for (const auto& id : ids) {
			matches[id] = std::vector<Coordinate>();
		}

		for (int i = a; i < b; ++i) {
			auto res = searchChunk(pathToRegion, i / DataExtractor::nbChunksInRegionX(), i % DataExtractor::nbChunksInRegionZ(), ids);

			for (const auto& id : ids) {
				matches[id].insert(matches[id].end(), res[id].begin(), res[id].end());
			}
		}

		return matches;
	};

	auto matches = pool.parallelize_loop(0, DataExtractor::nbChunksInRegion(), loop);

	for (size_t i = 0; i < matches.f.size(); ++i) {
		while (matches.f[i].wait_for(std::chrono::microseconds(0)) != std::future_status::ready) {
			std::this_thread::yield();
		}

		for (const auto& id : ids) {
			allMatches[id].insert(allMatches[id].end(), matches.f[i].get().begin(), matches.f[i].get().end());
		}
	}

	return allMatches;
}

std::map<int, std::vector<Coordinate>> BlockFinder::searchChunk(const std::filesystem::path & pathToRegion, int chunkX, int chunkY, const std::vector<int>& ids)
{
	std::map<int, std::vector<Coordinate>> matches;

	for (const auto& id : ids) {
		matches[id] = std::vector<Coordinate>();
	}

	auto chunk = DataExtractor::extractChunk(pathToRegion, chunkX, chunkY);

	for (size_t i = 0; i < chunk.size(); ++i) {
		for (size_t j = 0; j < chunk[i].size(); ++j) {
			for (size_t k = 0; k < chunk[i][j].size(); ++k) {
				if (matches.find(chunk[i][j][k]) != matches.end()) {
					matches[chunk[i][j][k]].push_back(Coordinate(i, j, k));
				}
			}
		}
	}

	return matches;
}
