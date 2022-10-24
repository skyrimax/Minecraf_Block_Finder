#include "Utility.hpp"

#include <filesystem>

bool is_empty(const std::filesystem::path & pFile)
{
	return std::filesystem::file_size(pFile) == 0;
}
