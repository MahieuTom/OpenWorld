/* 
 * File:   coordinate.h
 * Author: Tom Mahieu <tom.mahieu@student.uhasselt.be>
 * 
 * Created on May 17, 2014, 2;19 PM
 */
#ifndef COORDINATE_H
#define COORDINATE_H

#include <cmath>

class Coordinate
{
public:
    Coordinate();
    Coordinate(double x, double y, double z);
    ~Coordinate();
    void set(double x, double y, double z);

    /* snel aanroepen en aanpassen */
    double x;
    double y;
    double z;
};

#endif // COORDINATE_H
