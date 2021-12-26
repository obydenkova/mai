#ifndef D_VERTEX_H_
#define D_VERTEX_H_ 1

#include <iostream>

template<class T>
struct vertex {
    T x;
    T y;

};

template<class T>
std::istream& operator>> (std::istream& is, vertex<T>& p) {
    is >> p.x >> p.y;
    return is;
}

template<class T>
std::ostream& operator<< (std::ostream& os, const vertex<T>& p) {
    os << p.x << ' ' << p.y;
    return os;
}

#endif // D_VERTEX_H_
