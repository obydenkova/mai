#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "figure.h"

struct rectangle : figure{
private:
    point a1,a2,a3,a4;
public:
    point center() const override ;
    void print(std::ostream&) const override ;
    void printFile(std::ofstream&) const override ;
    double area() const override ;
    rectangle() = default;
    rectangle(std::istream& is);
    rectangle(std::ifstream& is);
};

#endif //_RECTANGLE_H_
