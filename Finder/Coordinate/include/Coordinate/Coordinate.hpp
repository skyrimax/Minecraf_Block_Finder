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

	int x;
	int y;
	int z;
};
