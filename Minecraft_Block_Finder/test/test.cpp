// test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "DataExtractor.h"

int main()
{
	auto chunk = DataExtractor::extractChunk("D:\\ATluncher\\servers\\DarkAge\\world\\region\\r.0.0.mca", 0, 0);

	

	return EXIT_SUCCESS;
}
