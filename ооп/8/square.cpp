#include "square.h"

square::square(std::istream& is) {
    is >> a1 >> a2 >> a3 >> a4;
}

double square::area() const {
    double vecX = a2.x - a1.x;
    double vecY = a2.y - a1.y;
    return vecX * vecX + vecY * vecY;
}

point square::center() const {
    double x,y;
    x = (a1.x + a2.x + a3.x + a4.x) / 4;
    y = (a1.y + a2.y + a3.y + a4.y) / 4;
    point p(x,y);
    return p;
}

std::ostream& square::print(std::ostream& os) const {
    os << "Square\n"<< a1 << a2 << a3 << a4;
    os << "Center: " << center() << "Area:" << area() << '\n';
    return os;
}
