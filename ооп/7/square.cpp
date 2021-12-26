#include "square.h"

#include <cmath>
#include "point.h"

point square::center() const {
    double x,y;
    x = (a1.x + a2.x + a3.x + a4.x) / 4;
    y = (a1.y + a2.y + a3.y + a4.y) / 4;
    point p(x,y);
    return p;
}

void square::print(std::ostream& os) const {
    os << "square\n"<< a1 << '\n' << a2 << '\n' << a3 << '\n' << a4 << '\n';
    os << "Center: " << center() << '\n' << "Area:" << area() << '\n';
}

void square::printFile(std::ofstream& of) const {
    of << "square\n"<< a1 << '\n' << a2 << '\n' << a3 << '\n' << a4 << '\n';
}

double square::area() const{
    double vecX = a2.x - a1.x;
    double vecY = a2.y - a1.y;

    return vecX * vecX + vecY * vecY;
}

square::square(std::istream& is) {
    is >> a1 >> a2 >> a3 >> a4;
}

square::square(std::ifstream& is) {
    is >> a1 >> a2 >> a3 >> a4;
}
