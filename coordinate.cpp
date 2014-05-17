#include "coordinate.h"

Coordinate::Coordinate() : x(0), y(0), z(0)
{
}

//-------------------------------------------------------------

Coordinate::Coordinate(double x, double y, double z) : x(x), y(y), z(z)
{
}

//-------------------------------------------------------------

Coordinate::~Coordinate()
{
}

//-------------------------------------------------------------

void Coordinate::rotate(double angle)
{
    // TODO:
    angle = 0;
}
