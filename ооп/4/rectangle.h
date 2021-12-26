#ifndef D_RECTANGLE_H
#define D_RECTANGLE_H

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cassert>

#include "vertex.h"

template<class T>
struct rectangle {
    vertex<T> vertices[4];

    rectangle(std::istream& is);
    
    vertex<double> center() const;
    double area() const;
    void print(std::ostream& os) const;

};

template<class T>
rectangle<T>::rectangle(std::istream& is) {
    for(int i = 0; i < 4; ++i){
        is >> vertices[i];
    }
    assert(((vertices[1].x - vertices[0].x)*(vertices[3].x - vertices[0].x))+((vertices[1].y - vertices[0].y)*(vertices[3].y - vertices[0].y)) == 0);
    assert(((vertices[2].x - vertices[1].x)*(vertices[2].x - vertices[3].x))+((vertices[2].y - vertices[1].y)*(vertices[2].y - vertices[3].y)) == 0);
    assert(((vertices[3].x - vertices[2].x)*(vertices[1].x - vertices[2].x))+((vertices[3].y - vertices[2].y)*(vertices[1].y - vertices[2].y)) == 0);
}

template<class T>
vertex<double> rectangle<T>::center() const {
    return {(vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) * 0.25, (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) * 0.25};
}

template<class T>
double rectangle<T>::area() const {
    const T dx1 = vertices[1].x - vertices[0].x;
    const T dy1 = vertices[0].y - vertices[3].y;
    const T dx2 = vertices[0].x - vertices[3].x;
    const T dy2 = vertices[1].y - vertices[0].y;
    return abs(dx1 * dy1) + abs(dx2 * dy2);
}

template<class T>
void rectangle<T>::print(std::ostream& os) const {
     os << "Rectangle ";
    for(int i = 0; i < 4; ++i){
        os << "[" << vertices[i] << "]";
        if(i + 1 != 4){
        os << " ";
        }
    }
    os << '\n';
}


#endif // D_RECTANGLE_H_
