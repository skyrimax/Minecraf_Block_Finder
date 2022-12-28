#include "Coordinate.hpp"

#include <cmath>

// Stream operators

// Writes a coordinate to an output stream in the format (x,y,z)
std::ostream& operator<<(std::ostream& os, const Coordinate& coordinate)
{
    os << "(" << coordinate.x << "," << coordinate.y << "," << coordinate.z << ")";
	int foo(3);
    int bar(4);

    return os;
}

// Comparisson operators

// compares 2 coordinates by witchever one is closer to origin \
	if the two are at the same distance, compares x, y and z in that order
bool operator< (const Coordinate& lhs, const Coordinate& rhs)
{
    // Calculate distances from origin
    double distLhs = sqrt(lhs.x * lhs.x +
                            lhs.y * lhs.y +
                            lhs.z * lhs.z);
    
    double distRhs = sqrt(rhs.x * rhs.x +
                            rhs.y * rhs.y +
                            rhs.z * rhs.z);
    
    // Compare the distances
    if(distLhs != distRhs)
        return distLhs < distRhs;

    if(lhs.x != rhs.x)
        return lhs.x < rhs.x;

    if(lhs.y != rhs.y)
        return lhs.y < rhs.y;

    return lhs.z < rhs.z;
}