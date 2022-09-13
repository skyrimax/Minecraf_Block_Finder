#pragma once
class Coordinate
{
public:
	Coordinate() = default;

	Coordinate(int x, int y, int z) :
		x { x }, y { y }, z { z }
	{
		
	}

	Coordinate(Coordinate &&) = default;

	Coordinate& operator=(Coordinate&) = default;

	int x;
	int y;
	int z;
};

