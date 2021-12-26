#ifndef D_VERTEX_HPP_
#define D_VERTEX_HPP_ 1

#include <iostream>

template<class T>
struct vertex {
    T x;
    T y;
};

template <class T>
std::istream& operator>> (std::istream& is, vertex<T>& p) {
    is >> p.x >> p.y;
    return is;
}

template<class T>
std::ostream& operator<< (std::ostream& os, const vertex<T>& p) {
    os << '[' << ' ' << p.x << ' ' << p.y << ' ' << ']';
    return os;
}

template <class T>
vertex<T> operator+ (vertex<T> p1, vertex<T> p2) {
    vertex<T> p;
    p.x = p1.x + p2.x;
    p.y = p1.y + p2.y;
    return p;
}

template <class T>
vertex<T>& operator/ (vertex<T>& p, int num) {
    p.x = p.x / num;
    p.y = p.y / num;
    return p;
}

#endif // D_VERTEX_HPP_