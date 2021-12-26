#pragma once

#include "figure.h"
#include <exception>

struct trapeze : public fig{
	private:
    point p1_, p2_, p3_, p4_;
public:
    trapeze() = default;
    trapeze(point p1, point p2, point p3, point p4);
	trapeze(std::istream& is){
        is >> p1_ >> p2_ >> p3_ >> p4_;
	}
    point center() const override;
    double square() const override;
    void print(std::ostream& os) const override;
    
	

};
