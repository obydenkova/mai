#ifndef _D_RECTANGLE_H_
#define _D_RECTANGLE_H_

#include "figure.h"

class rectangle : public figure {
public:
    rectangle() = default;
    rectangle(std::istream& is) ;
    double area() const override;
    point center() const override;
    std::ostream& print(std::ostream& os) const override;
private:
    point a1, a2, a3, a4;
};

#endif // _D_RECTANGLE_H_
