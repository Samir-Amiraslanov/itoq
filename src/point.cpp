#include "../include/point.h"

Point::Point(double a, double b) : x(a), y(b) {}

double Point::get_x() const { 
    return x; 
}

double Point::get_y() const { 
    return y; 
}