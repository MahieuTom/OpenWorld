/* 
 * File:   coordinate.cpp
 * Author: Tom Mahieu <tom.mahieu@student.uhasselt.be>
 * 
 * Created on May 17, 2014, 2;19 PM
 */
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

void Coordinate::set(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}