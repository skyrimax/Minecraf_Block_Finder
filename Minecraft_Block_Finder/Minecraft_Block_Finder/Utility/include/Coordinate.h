#pragma once
struct Coordinate
{
	Coordinate() = default;

	Coordinate(int x, int y, int z) :
		x{ x }, y{ y }, z{ z }
	{
		
	}

	int x;
	int y;
	int z;
};
