#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <iostream>
#include "vector"
#include "point.h"

point operator + (point lhs, point rhs);
point operator - (point lhs, point rhs);
point operator / (point lhs, double a);
point operator * (point lhs, double a);

class Vector {
public:
    explicit Vector(double a, double b);
    explicit Vector(point a, point b);
    bool operator == (Vector rhs);
    Vector operator - ();
    friend double operator * (Vector lhs, Vector rhs);
    double length() const;
    double x;
    double y;
};

bool is_parallel(const Vector& lhs, const Vector& rhs);
double point_and_line_distance(point p1, point p2, point p3);


struct fig{
public:
    virtual point center() const = 0;
    virtual double square() const = 0;
    virtual void print(std::ostream& os) const = 0;                                                                 
    virtual ~fig () {}    

};

std::ostream& operator << (std::ostream& os, const point& p);
std::istream& operator >> (std::istream& is, point& p);
std::ostream& operator << (std::ostream& os, const fig& f);
#endif