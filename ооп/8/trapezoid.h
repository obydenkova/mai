#ifndef _D_TRAPEZOID_H_
#define _D_TRAPEZOID_H_

#include "figure.h"

class trapezoid : public figure {
public:
    trapezoid() = default;
    trapezoid(std::istream& is);
    double area() const override;
    point center() const override;
    std::ostream& print(std::ostream& os) const override;
private:
    point a1, a2, a3, a4;
};

#endif // _D_TRAPEZOID_H_
