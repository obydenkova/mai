#ifndef _D_SQUARE_H_
#define _D_SQUARE_H_

#include "figure.h"

class square : public figure {
public:
    square() = default;
    square(std::istream& is);
    double area() const override;
    point center() const override;
    std::ostream& print(std::ostream&) const override;
private:
    point a1, a2, a3, a4;
};

#endif // _D_SQUARE_H_
