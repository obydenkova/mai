#include<iostream>
#include<vector>
#include<cmath>
#include<string.h>

#include "quadrate.h"
#include "figure.h"
#include "point.h"

void quadrate::print(std::ostream& os) const{
    os << "quadrate: ";
    os << "(" << a.x << ", " << a.y << ")" << " ";
    os << "(" << b.x << ", " << b.y << ")" << " "; 
    os << "(" << c.x << ", " << c.y << ")" << " ";
    os << "(" << d.x << ", " << d.y << ")" << " ";  
    os << '\n';
}

double quadrate::square() const{
    double scalar1 = scalar_mult(b, a, c);
    double scalar2 = scalar_mult(b, a, d); 
    double scalar3 = scalar_mult(c, a, d);
    double mid;
    if(scalar1 == 0){
        mid = segment_length(a, b);
    } else if(scalar2 == 0){
        mid = segment_length(a, d);
    } else if(scalar3 == 0){
        mid = segment_length(a, c);
    }
    return mid * mid;
}


point quadrate::center() const{
    double scalar1 = scalar_mult(b, a, c);
    double scalar2 = scalar_mult(b, a, d); 
    double scalar3 = scalar_mult(c, a, d);
    double midx, midy;
    if(scalar1 == 0){
        midx = (c.x + b.x) * 0.5;
        midy = (c.y + b.y) * 0.5;
    } else if(scalar2 == 0){
        midx = (d.x + b.x) * 0.5;
        midy = (d.y + b.y) * 0.5;
    } else if(scalar3 == 0){
        midx = (c.x + d.x) * 0.5;
        midy = (c.y + d.y) * 0.5;
    }
    return point{midx, midy};
}


