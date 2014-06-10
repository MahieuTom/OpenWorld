#ifndef COORDINATE_H
#define COORDINATE_H

#include <cmath>

class Coordinate
{
public:
    Coordinate();
    Coordinate(double x, double y, double z);
    ~Coordinate();

    void rotate(double angle);
    void set(double x, double y, double z);

    /* snel aanroepen en aanpassen */
    double x;
    double y;
    double z;
};

#endif // COORDINATE_H
