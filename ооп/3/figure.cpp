#include "figure.h"
#include <numeric>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

point operator + (point lhs, point rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

point operator - (point lhs, point rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

point operator / (point lhs, double a) {
    return { lhs.x / a, lhs.y / a};
}

point operator * (point lhs, double a) {
    return {lhs.x * a, lhs.y * a};
}

bool operator < (point lhs, point rhs) {
    return (lhs.x * lhs.x + lhs.y * lhs.y) < (lhs.x * lhs.x + lhs.y * lhs.y);
}

double operator * (Vector lhs, Vector rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

bool is_parallel(const Vector& lhs, const Vector& rhs) {
    return (lhs.x * rhs.y - lhs.y * rhs.y) == 0;
}

bool Vector::operator == (Vector rhs) {
    return
        std::abs(x - rhs.x) < std::numeric_limits<double>::epsilon() * 100
        && std::abs(y - rhs.y) < std::numeric_limits<double>::epsilon() * 100;
}

double Vector::length() const {
    return sqrt(x*x + y*y);
}

Vector::Vector(double a, double b)
: x(a), y(b) {

}

Vector::Vector(point a, point b)
: x(b.x - a.x), y(b.y - a.y){

}

Vector Vector::operator - () {
    return Vector(-x, -y);
}


double point_and_line_distance(point p1, point p2, point p3) {
    double A = p2.y - p3.y;
    double B = p3.x - p2.x;
    double C = p2.x*p3.y - p3.x*p2.y;
    return (std::abs(A*p1.x + B*p1.y + C) / sqrt(A*A + B*B));
}

std::ostream& operator << (std::ostream& os, const point& p) {
    return os << p.x << " " << p.y;
}

std::istream& operator >> (std::istream& is, point& p) {
    return is >> p.x >> p.y;
}

std::ostream& operator << (std::ostream& os, const fig& fig) {
    fig.print(os);
    return os;
}

std::istream& operator >> (std::istream& is, fig& fig) {
    
    return is;
}