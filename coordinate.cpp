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
    angle = angle / 360.0 * 2 * 3.141; // Omzetten naar radialen.

    double xNew = x * cos(angle)  + y * sin(angle);
    double yNew = x * -sin(angle) + y * cos(angle);

    x = xNew;
    y = yNew;
}

//-------------------------------------------------------------

void Coordinate::set(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}