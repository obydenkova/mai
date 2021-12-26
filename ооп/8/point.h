#ifndef _D_POINT_H_
#define _D_POINT_H_
#include <iostream>

struct point {
    double x,y;
    point (double a, double b) {x = a, y = b;};
    point() = default;
};

point operator+ (point lhs, point rhs);
point operator- (point lhs, point rhs);
point operator/ (point p, double t);
std::istream &operator>> (std::istream &is, point &p );
std::ostream &operator<< (std::ostream &os, const point &p );

#endif // _D_POINT_H_
