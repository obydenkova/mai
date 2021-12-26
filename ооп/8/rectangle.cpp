#include "rectangle.h"

rectangle::rectangle(std::istream& is) {
    is >> a1 >> a2 >> a3 >> a4;
}

double rectangle::area() const {
    double xHeight = a2.x - a1.x;
    double yHeight = a2.y - a1.y;

    double xWidth = a3.x - a2.x;
    double yWidth = a3.y - a2.y;

    return sqrt(xHeight * xHeight + yHeight * yHeight) * sqrt(xWidth * xWidth + yWidth * yWidth);
}

point rectangle::center() const {
    double x,y;
    x = (a1.x + a2.x + a3.x + a4.x) / 4;
    y = (a1.y + a2.y + a3.y + a4.y) / 4;
    point p(x,y);
    return p;
}

std::ostream& rectangle::print(std::ostream& os) const {
    os << "Rectangle\n"<< a1 << a2 << a3 << a4;
    os << "Center: " << center() << "Area:" << area() << '\n';
    return os;
}
