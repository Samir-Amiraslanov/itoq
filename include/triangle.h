#pragma once
#include "point.h"
#include <fstream>

class Triangle {
    Point p1, p2, p3;
    double dist(const Point& a, const Point& b) const;

public:
    Triangle();
    Triangle(const Point& a, const Point& b, const Point& c);

    bool is_valid() const;
    bool ravnobedr() const;
    double perimeter() const;
    double area() const;
    void show(std::ofstream &fout) const;
};