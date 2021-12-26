#ifndef D_SQUARE_HPP_
#define D_SQUARE_HPP_ 1

#include <iostream>
#include <assert.h>
#include <math.h>

#include "vertex.hpp"

template<class T>
struct Square {
public:
    Square(std::istream &is);
    bool correct() const;

    vertex<double> center() const;
    double area() const;
    void print() const;
   

private:
    vertex<T> a1,a2,a3,a4;
};



template<class T>
Square<T>::Square(std::istream &is){
    is >> a1 >> a2 >> a3 >> a4;
    assert(correct());
}

template<class T>
bool Square<T>::correct() const {
    T vec1_x = a2.x - a1.x;
    T vec1_y = a2.y - a1.y;

    T vec2_x = a3.x - a2.x;
    T vec2_y = a3.y - a2.y;

    T vec3_x = a4.x - a1.x;
    T vec3_y = a4.y - a1.y;

    T vec4_x = a4.x - a3.x;
    T vec4_y = a4.y - a3.y;

    T dotProduct1 = vec1_x * vec2_x + vec1_y * vec2_y;
    T dotProduct2 = vec3_x * vec1_x + vec3_y * vec1_y;
    T dotProduct3 = vec3_x * vec4_x + vec3_y * vec4_y;

    T vec1_length = sqrt(vec1_x * vec1_x + vec1_y * vec1_y);
    T vec2_length = sqrt(vec2_x * vec2_x + vec2_y * vec2_y);

    if (dotProduct1 == 0 && dotProduct2 == 0 && dotProduct3 == 0 && vec1_length == vec2_length) {
        return true;
    }
    return false;
}

template<class T>
vertex<double> Square<T>::center() const {
    vertex<double> p;
    p.x = (a1.x + a2.x + a3.x + a4.x) / 4;
    p.y = (a1.y + a2.y + a3.y + a4.y) / 4;
    return p;
}


template<class T>
double Square<T>::area() const {
    const T vecX = a2.x - a1.x;
    const T vecY = a2.y - a1.y;

    return vecX * vecX + vecY * vecY;
}

template<class T>
void Square<T>::print() const {
    std::cout << "Vertices: " << a1 << " " << a2 << " " << a3 << " " << a4 << '\n';
    std::cout << "Area:" << area() << std::endl;
    std::cout << "Center:" << center() << std::endl;
}
#endif
