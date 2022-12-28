#include "Coordinate.hpp"

// Stream operators

// Writes a coordinate to an output stream in the format (x,y,z)
std::ostream& operator<<(std::ostream& os, const Coordinate& coordinate)
{
    os << "(" << coordinate.x << "," << coordinate.y << "," << coordinate.z << ")";

    return os;
}