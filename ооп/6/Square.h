#pragma once

#include <iostream>
#include <exception>
#include "Point.h"


template <typename T>
class Square {
public:
    Square() = default;
    Square(Point<T> p1, Point<T> p2, Point<T>p3, Point<T> p4);
    Point<T> Center() const;
    double Area() const;
    void Print(std::ostream& os) const;
    void Scan(std::istream& is);

private:
    Point<T> p1_, p2_, p3_, p4_;
};

template <typename T>
Square<T>::Square(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4)
        :  p1_(p1), p2_(p2), p3_(p3), p4_(p4){
    Vector<T> v1(p1_, p2_), v2(p3_, p4_);
    if (v1 = Vector<T>(p1_, p2_), v2 = Vector<T>(p3_, p4_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p3_, p4_);
        }
    } else if (v1 = Vector<T>(p1_, p3_), v2 = Vector<T>(p2_, p4_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p2_, p4_);
        }
        std::swap(p2_, p3_);
    } else if (v1 = Vector<T>(p1_, p4_), v2 = Vector<T>(p2_, p3_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p2_, p3_);
        }
        std::swap(p2_, p4_);
        std::swap(p3_, p4_);
    } else {
        throw std::logic_error("At least 2 sides of Square must be parallel");
    }

}

template <typename T>
Point<T> Square<T>::Center() const {
    return (p1_ + p2_ + p3_ + p4_) / 4;
}

template<typename T>
double Square<T>::Area() const {
    double height = point_and_line_distance(p1_, p3_, p4_);
    return (Vector<T>(p1_, p2_).length() + Vector<T>(p3_, p4_).length()) * height / 2;
}

template<typename T>
void Square<T>::Print(std::ostream& os) const {
    os << "Square p1:" << p1_ << ", p2:" << p2_ << ", p3:" << p3_ << ", p4:" << p4_;
}

template <typename T>
void Square<T>::Scan(std::istream &is) {
    Point<T> p1,p2,p3,p4;
    is >> p1 >> p2 >> p3 >> p4;
    *this = Square(p1,p2,p3,p4);
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Square<T>& trap) {
    trap.Print(os);
    return os;
}

template <typename T>
std::istream& operator >> (std::istream& is, Square<T>& trap) {
    trap.Scan(is);
    return is;
}

