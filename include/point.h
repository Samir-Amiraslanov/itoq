#pragma once

class Point {
    double x, y;
public:
    Point(double a = 0.0, double b = 0.0);
    double get_x() const;
    double get_y() const;
};
