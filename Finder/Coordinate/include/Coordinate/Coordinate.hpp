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

	// Comparisson operators

	/**
	 * @brief compares 2 coordinates by witchever one is closer to origin \
	 * 			if the two are at the same distance, compares x, y and z in that order
	 * 
	 * @param lhs 
	 * @param rhs 
	 * @return true if the lhs coordinate is closer to origin or it x, y, z is smaller (first one to differ)
	 * @return false otherwise
	 */
	friend bool operator< (const Coordinate& lhs, const Coordinate& rhs);

	friend bool operator> (const Coordinate& lhs, const Coordinate& rhs);
	friend bool operator<= (const Coordinate& lhs, const Coordinate& rhs);
	friend bool operator<= (const Coordinate& lhs, const Coordinate& rhs);

	/**
	 * @brief compare if 2 coordinates are the same, which means x, y, z are equal between the 2 operands
	 * 
	 * @param lhs 
	 * @param rhs 
	 * @return true if x, y and z are equals between lhs and rhs
	 * @return false otherwise
	 */
	friend bool operator== (const Coordinate& lhs, const Coordinate& rhs);

	friend bool operator!= (const Coordinate& lhs, const Coordinate& rhs);

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
