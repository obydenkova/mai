#include <iostream>
#include "point.h"
#include <cmath>

#ifndef _D_FIGURE_H_
#define _D_FIGURE_H_

struct figure {
    virtual point center() const = 0;
    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual double area() const = 0;
    virtual ~figure() {}
};

#endif //_D_FIGURE_H_