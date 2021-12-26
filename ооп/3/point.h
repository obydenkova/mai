#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>

typedef struct{
    double x, y;
}
point;
std::istream& operator>> (std::istream& is, point &p);
std::ostream& operator<<(std::ostream&, point const&);
std::ostream& operator<< (std::ostream& os, const point &p);

bool operator== (point a, point b);

double scalar_mult(point a_end, point top_begin, point b_end);
double segment_length(point a, point b);

#endif
