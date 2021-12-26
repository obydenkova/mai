#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "figure.h"

struct rectangle : public fig{
private:
    point a, b, c, d;
public:
       rectangle() = default;
        rectangle(std::istream& is){
        is >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        double scalar1 = scalar_mult(b, a, c);
        double scalar2 = scalar_mult(b, a, d); 
        double scalar3 = scalar_mult(c, a, d);
        double scalar01, scalar02, scalar03;
        if(scalar1 == 0){
            scalar01 = scalar_mult(d, b, a); 
            scalar02 = scalar_mult(b, d, c); 
            scalar03 = scalar_mult(a, c, d);     
            if(!(scalar01 == 0 && scalar02 == 0 && scalar03 == 0)){
                throw std::logic_error("It is not rectangle");
            }
        } else if(scalar2 == 0){
            scalar01 = scalar_mult(a, b, c);
            scalar02 = scalar_mult(a, d, c);
            scalar03 = scalar_mult(b, c, d);     
            if(!(scalar01 == 0 && scalar02 == 0 && scalar03 == 0)){
                throw std::logic_error("It is not rectangle");
            }
        } else if(scalar3 == 0){
            scalar01 = scalar_mult(c, b, d); 
            scalar02 = scalar_mult(a, d, b);
            scalar03 = scalar_mult(b, c, a);   
            if(!(scalar01 == 0 && scalar02 == 0 && scalar03 == 0)){
                throw std::logic_error("It is not rectangle");
            }  
        } else {
            throw std::logic_error("It is not rectangle");
        }
    }

    point center() const override;
    double square() const override;
    void print(std::ostream& os) const override;
};

#endif
