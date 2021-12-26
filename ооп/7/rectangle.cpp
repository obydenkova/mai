#include <cmath>

#include "rectangle.h"

point rectangle::center() const {
    double x,y;
    x = (a1.x + a2.x + a3.x + a4.x) / 4;
    y = (a1.y + a2.y + a3.y + a4.y) / 4;
    point p(x,y);
    return p;
}

void rectangle::print(std::ostream& os) const {
    os << "rectangle\n"<< a1 << '\n' << a2 << '\n' << a3 << '\n' << a4 << '\n';
    os << "Center: " << center() << '\n' << "Area:" << area() << '\n';
}

void rectangle::printFile(std::ofstream &of) const {
    of << "rectangle\n"<< a1 << '\n' << a2 << '\n' << a3 << '\n' << a4 << '\n';
}

double rectangle::area() const {
    double xHeight = a2.x - a1.x;
    double yHeight = a2.y - a1.y;

    double xWidth = a3.x - a2.x;
    double yWidth = a3.y - a2.y;

    return sqrt(xHeight * xHeight + yHeight * yHeight) * sqrt(xWidth * xWidth + yWidth * yWidth);
}

rectangle::rectangle(std::istream& is) {
    is >> a1 >> a2 >> a3 >> a4;
}

rectangle::rectangle(std::ifstream& is) {
    is >> a1 >> a2 >> a3 >> a4;
}