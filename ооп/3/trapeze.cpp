#include "trapeze.h"
#include<iostream>
#include<vector>
#include<cmath>
#include<string.h>


#include "figure.h"
#include "point.h"
#include "trapeze.h"

trapeze::trapeze(point p1, point p2, point p3, point p4): 
 p1_(p1), p2_(p2), p3_(p3), p4_(p4){
    Vector v1(p1_, p2_), v2(p3_, p4_);
    if (v1 = Vector(p1_, p2_), v2 = Vector(p3_, p4_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p3_, p4_);
        }
    } else if (v1 = Vector(p1_, p3_), v2 = Vector(p2_, p4_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p2_, p4_);
        }
        std::swap(p2_, p3_);
    } else if (v1 = Vector(p1_, p4_), v2 = Vector(p2_, p3_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p2_, p3_);
        }
        std::swap(p2_, p4_);
        std::swap(p3_, p4_);
    } else {
        throw std::logic_error("At least 2 sides of trapeze must be parallel");
    }

}

point trapeze::center() const {
    return (p1_ + p2_ + p3_ + p4_) / 4;
}

double trapeze::square() const {
    double height = point_and_line_distance(p1_, p3_, p4_);
    return (Vector(p1_, p2_).length() + Vector(p3_, p4_).length()) * height / 2;
}
 
void trapeze::print(std::ostream& os) const {
    os << "trapeze: (" << p1_ << ") (" << p2_ << ") (" << p3_ << ") (" << p4_<< ")" << "\n";
}
