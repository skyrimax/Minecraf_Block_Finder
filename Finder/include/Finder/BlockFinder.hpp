#pragma once

#include <map>
#include <vector>
#include <string>
#include <filesystem>
#include "BS_thread_pool.hpp"

#include "Output.hpp"
#include "Coordinate.hpp"

class BlockFinder
{
public:
	BlockFinder(Output::OutputType outputType = Output::OutputType::CSV) :
		pool{std::thread::hardware_concurrency()}
	{
		
	}

	void Search(const std::filesystem::path& pathToWorld = "C:\\world",
		const std::vector<int>& dims = { 0 }, const std::vector<int>& id = { 1 });

private:

	std::map<int, std::vector<Coordinate>> searchDim(const std::filesystem::path& pathToWorld, int dim, std::vector<int> ids);
	std::map<int, std::vector<Coordinate>> searchRegion(const std::filesystem::path& pathToRegion, const std::vector<int>& ids);
	std::map<int, std::vector<Coordinate>> searchChunk(const std::filesystem::path& pathToRegion, int chunkX, int chunkY, const std::vector<int>& ids);

	std::filesystem::path pathToDimData(std::filesystem::path pathToWorld, int dim);

	void output(std::map<int, std::map<int, std::vector<Coordinate>>> matches);

	Output::OutputType m_outputType;
	BS::thread_pool pool;
};
