#ifndef  _POINT_H_
#define  _POINT_H_

#include <iostream>

struct point {
    double x, y;
    point (double a, double b) {x = a, y = b;};
    point() = default;
};

std::istream& operator >> (std::istream& is,point& p );
std::ostream& operator << (std::ostream& os,const point& p);

#endif // _POINT_H_
