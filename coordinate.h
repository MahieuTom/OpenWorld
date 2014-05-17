#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
public:
    Coordinate();
    Coordinate(double x, double y, double z);
    ~Coordinate();

    void rotate(double angle);

    /* snel aanroepen en aanpassen */
    double x;
    double y;
    double z;
};

#endif // COORDINATE_H
