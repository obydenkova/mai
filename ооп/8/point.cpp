#include "point.h"

point operator+ (point lhs, point rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

point operator- (point lhs, point rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

point operator/ (point p, double t) {
    return {p.x / t, p.y / t};
}

std::istream &operator>>(std::istream &is, point &p) {
    is >> p.x >> p.y;
    return is;
}

std::ostream &operator<< (std::ostream &os, const point &p ) {
    os << p.x << " " << p.y << std::endl;
    return os;
}
