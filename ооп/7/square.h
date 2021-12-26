#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "figure.h"

struct square : figure {
private:
    point a1,a2,a3,a4;
public:
    point center() const override ;
    void print(std::ostream&) const  override ;
    void printFile(std::ofstream&) const override ;
    double area() const override ;
    square() = default;
    square(std::istream& is);
    square(std::ifstream& is);
};

#endif //_SQUARE_H_
