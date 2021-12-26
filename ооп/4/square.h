#ifndef D_SQUARE_H_
#define D_SQUARE_H_ 1

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cassert>

#include "vertex.h"

template<class T>
struct square {
    vertex<T> vertices[4];

    square(std::istream& is);
    
    vertex<double> center() const;
    double area() const;
    void print(std::ostream& os) const;

};

template<class T>
square<T>::square(std::istream& is) {
    for(int i = 0; i < 4; ++i){
        is >> vertices[i];
    }
    assert(((vertices[1].x - vertices[0].x)*(vertices[3].x - vertices[0].x))+((vertices[1].y - vertices[0].y)*(vertices[3].y - vertices[0].y)) == 0);
    assert(((vertices[2].x - vertices[1].x)*(vertices[2].x - vertices[3].x))+((vertices[2].y - vertices[1].y)*(vertices[2].y - vertices[3].y)) == 0);
    assert(((vertices[3].x - vertices[2].x)*(vertices[1].x - vertices[2].x))+((vertices[3].y - vertices[2].y)*(vertices[1].y - vertices[2].y)) == 0);
    assert((vertices[1].x - vertices[0].x) == (vertices[0].y - vertices[3].y));
    assert((vertices[2].x - vertices[1].x) == (vertices[1].y - vertices[0].y));
    assert((vertices[3].x - vertices[2].x) == (vertices[2].y - vertices[1].y));
}

template<class T>
vertex<double> square<T>::center() const {
    return {(vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) * 0.25, (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) * 0.25};
}

template<class T>
double square<T>::area() const {
    const T d1 = vertices[0].x - vertices[1].x;
    const T d2 = vertices[3].x - vertices[0].x;
    return abs(d1 * d1) + abs(d2 * d2);
}

template<class T>
void square<T>::print(std::ostream& os) const {
     os << "Square ";
    for(int i = 0; i < 4; ++i){
        os << "[" << vertices[i] << "]";
        if(i + 1 != 4){
        os << " ";
        }
    }
    os << '\n';
}

#endif // D_SQUARE_H_
