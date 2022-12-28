#pragma once

#include <ostream>

struct Coordinate
{
	// Constructors
	Coordinate() = default;

	Coordinate(int x, int y, int z) :
		x{ x }, y{ y }, z{ z }
	{
		
	}

	Coordinate(const Coordinate &) = default;

	Coordinate(Coordinate &&) = default;

	// Assigment operators
	Coordinate& operator= (const Coordinate&) = default;
	Coordinate& operator= (Coordinate&&) = default;

	int x;
	int y;
	int z;
};

	// Stream operators

	/**
	 * @brief Writes a coordinate to an output stream in the format (x,y,z)
	 * 
	 * @param os Output stream to witch the Coordinate will be writen
	 * @param coordinate Coordinate object to be writen
	 * @return the output stream
	 */
	std::ostream& operator<<(std::ostream& os, const Coordinate& coordinate);
