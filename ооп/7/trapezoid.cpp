#include "trapezoid.h"

point trapezoid::center() const {
    double x,y;
    x = (a1.x + a2.x + a3.x + a4.x) / 4;
    y = (a1.y + a2.y + a3.y + a4.y) / 4;
    point p(x,y);
    return p;
}

void trapezoid::print(std::ostream& os) const {
    os << "trapezoid\n"<< a1 << '\n' << a2 << '\n' << a3 << '\n' << a4 << '\n';
    os << "Center: " << center() << '\n' << "Area:" << area() << '\n';
}

void trapezoid::printFile(std::ofstream& of) const {
    of << "trapezoid\n"<< a1 << '\n' << a2 << '\n' << a3 << '\n' << a4 << '\n';
}

double trapezoid::area() const {
    double area1 = 0.5 * abs((a1.x - a2.x) * (a4.y - a2.y) - (a4.x - a2.x) * (a3.y - a2.y));
    double area2 = 0.5 * abs((a1.x - a2.x) * (a3.y - a2.y) - (a4.x - a2.x) * (a1.y - a2.y));
    
    return area1 + area2;
}

trapezoid::trapezoid(std::istream& is) {
    is >> a1 >> a2 >> a3 >> a4;
}

trapezoid::trapezoid(std::ifstream& is) {
    is >> a1 >> a2 >> a3 >> a4;
}