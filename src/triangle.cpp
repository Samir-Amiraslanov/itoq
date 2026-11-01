#include "../include/triangle.h"
#include <cmath>

Triangle::Triangle() : p1(0,0), p2(0,0), p3(0,0) {}

Triangle::Triangle(const Point& a, const Point& b, const Point& c) : p1(a), p2(b), p3(c) {}

double Triangle::dist(const Point& a, const Point& b) const {
    double dx = a.get_x() - b.get_x();
    double dy = a.get_y() - b.get_y();
    return sqrt(dx*dx + dy*dy);
}

bool Triangle::is_valid() const {
    double a = dist(p1, p2);
    double b = dist(p2, p3);
    double c = dist(p1, p3);
    return (a+b > c) && (a+c > b) && (b+c > a);
}

bool Triangle::ravnobedr() const {
    double a = dist(p1, p2);
    double b = dist(p2, p3);
    double c = dist(p1, p3);
    double eps = 1e-16;
    return std::abs(a-b) < eps || std::abs(a-c) < eps || std::abs(b-c) < eps;
}

double Triangle::perimeter() const {
    return dist(p1, p2) + dist(p2, p3) + dist(p3, p1);
}

double Triangle::area() const {
    double a = dist(p1, p2);
    double b = dist(p2, p3);
    double c = dist(p3, p1);
    double p = (a+b+c) / 2.0;
    double t = p*(p-a)*(p-b)*(p-c);
    if (t <= 0) return 0;
    return sqrt(t);
}

void Triangle::show(std::ofstream &fout) const {
    fout << "( " << p1.get_x() << "," << p1.get_y() << " ) "
         << "( " << p2.get_x() << "," << p2.get_y() << " ) "
         << "( " << p3.get_x() << "," << p3.get_y() << " ) ";
}