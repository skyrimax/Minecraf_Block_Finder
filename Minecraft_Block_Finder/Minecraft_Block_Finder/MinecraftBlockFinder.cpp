// Minecraft_Block_Finder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>

#include <thread>

#include "argparse.hpp"

#include "BlockFinder.h"

argparse::ArgumentParser createParser();

int main(int argc, char* argv[])
{
	argparse::ArgumentParser program = createParser();

	try {
		program.parse_args(argc, argv);
	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << program;

		std::exit(1);
	}

	std::string path = program.get("path");
	std::vector<int> dims = program.get<std::vector<int>>("dim");
	int id = program.get<int>("BlockID");

	std::cout << "Path to save : " << path << std::endl
		<< "Block to search : " << id << std::endl
		<< "Dimension to analyse : ";

	for (const auto& dim : dims) {
		std::cout << dim << " ";
	}

	//BlockFinder finder(path, dims, id);

	//finder.Search();

	std::cout << std::endl << std::endl;

	return EXIT_SUCCESS;
}

argparse::ArgumentParser createParser() {
	argparse::ArgumentParser parser("Minecraft Block Finder");

	parser.add_argument("path")
		.required()
		.help("Path to save folder");

	parser.add_argument("BlockID")
		.required()
		.scan<'d', int>()
		.help("ID number of the block to search");

	parser.add_argument("dim")
		.default_value<int>(0)
		.scan<'d', int>()
		.remaining()
		.help("Dimensions to search");

	return parser;
}
