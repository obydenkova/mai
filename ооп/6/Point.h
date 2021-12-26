#pragma once

#include <numeric>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

template <typename T>
struct Point {
    T x = 0;
    T y = 0;
};

template <typename T>
class Vector {
public:
    explicit Vector(T a, T b);
    explicit Vector(Point<T> a, Point<T> b);
    bool operator == (Vector rhs);
    Vector operator - ();
    double length() const;
    T x;
    T y;
};

template <typename T>
Point<T> operator + (Point<T> lhs, Point<T> rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template <typename T>
Point<T> operator - (Point<T> lhs, Point<T> rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template <typename T>
Point<T> operator / (Point<T> lhs, double a) {
    return { lhs.x / a, lhs.y / a};
}

template <typename T>
Point<T> operator * (Point<T> lhs, double a) {
    return {lhs.x * a, lhs.y * a};
}

template <typename T>
bool operator < (Point<T> lhs, Point<T> rhs) {
    return (lhs.x * lhs.x + lhs.y * lhs.y) < (lhs.x * lhs.x + lhs.y * lhs.y);
}

template <typename T>
double operator * (Vector<T> lhs, Vector<T> rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename T>
bool is_parallel(const Vector<T>& lhs, const Vector<T>& rhs) {
    return (lhs.x * rhs.y - lhs.y * rhs.y) == 0;
}

template <typename T>
bool Vector<T>::operator == (Vector<T> rhs) {
    return
            std::abs(x - rhs.x) < std::numeric_limits<double>::epsilon() * 100
            && std::abs(y - rhs.y) < std::numeric_limits<double>::epsilon() * 100;
}

template <typename T>
double Vector<T>::length() const {
    return sqrt(x*x + y*y);
}

template <typename T>
Vector<T>::Vector(T a, T b)
        : x(a), y(b) {

}

template <typename T>
Vector<T>::Vector(Point<T> a, Point<T> b)
        : x(b.x - a.x), y(b.y - a.y){

}

template <typename T>
Vector<T> Vector<T>::operator - () {
    return Vector(-x, -y);
}

template <typename T>
bool is_perpendecular(const Vector<T>& lhs, const Vector<T>& rhs) {
    return (lhs * rhs) == 0;
}

template <typename T>
double point_and_line_distance(Point<T> p1, Point<T> p2, Point<T> p3) {
    double A = p2.y - p3.y;
    double B = p3.x - p2.x;
    double C = p2.x*p3.y - p3.x*p2.y;
    return (std::abs(A*p1.x + B*p1.y + C) / std::sqrt(A*A + B*B));
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Point<T>& p) {
    return os << p.x << " " << p.y;
}

template <typename T>
std::istream& operator >> (std::istream& is, Point<T>& p) {
    return is >> p.x >> p.y;
}


