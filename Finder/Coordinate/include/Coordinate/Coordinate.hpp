#pragma once
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
