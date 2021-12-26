#ifndef _TRAPEZOID_H_
#define _TRAPEZOID_H_

#include "figure.h"

struct trapezoid : figure {
private:
    point a1,a2,a3,a4;
public:
    point center() const override ;
    void print(std::ostream&) const override;
    void printFile(std::ofstream&) const override;
    double area() const override;
    trapezoid() = default;
    trapezoid(std::istream& is);
    trapezoid(std::ifstream& is);
};

#endif //_TRAPEZOID_H_
