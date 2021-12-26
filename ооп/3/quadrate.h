#ifndef _QUADRATE_H_
#define _QUADRATE_H_

#include "figure.h"
#include "point.h"

struct quadrate : public fig{
private:
    point a, b, c, d;
public:
       quadrate() = default;
    quadrate(std::istream& is){
        is >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        double scalar1 = scalar_mult(b, a, c);
        double scalar2 = scalar_mult(b, a, d); 
        double scalar3 = scalar_mult(c, a, d);
        double scalar01, scalar02, scalar03, scalar_diag;
        if(scalar1 == 0){
             scalar01 = scalar_mult(d, b, a); 
             scalar02 = scalar_mult(b, d, c); 
             scalar03 = scalar_mult(a, c, d);   
             scalar_diag = (c.x - b.x)*(d.x - a.x) + (c.y - b.y)*(d.y - a.y);
             if(!(scalar01 == 0 && scalar02 == 0 && scalar03 == 0 && scalar_diag == 0)){
                 throw std::logic_error("It is not quadrate");
             }
        } else if(scalar2 == 0){
            scalar01 = scalar_mult(a, b, c);
            scalar02 = scalar_mult(a, d, c);
            scalar03 = scalar_mult(b, c, d);   
            scalar_diag = (d.x - b.x)*(c.x - a.x) + (d.y - b.y)*(c.y - a.y);
            if(!(scalar01 == 0 && scalar02 == 0 && scalar03 == 0 && scalar_diag == 0)){
                throw std::logic_error("It is not quadrate");      
            }
        } else if(scalar3 == 0){
            scalar01 = scalar_mult(c, b, d); 
            scalar02 = scalar_mult(a, d, b);
            scalar03 = scalar_mult(b, c, a);   
            scalar_diag = (d.x - c.x)*(b.x - a.x) + (d.y - c.y)*(b.y - a.y);
            if(!(scalar01 == 0 && scalar02 == 0 && scalar03 == 0 && scalar_diag == 0)){
                throw std::logic_error("It is not quadrate");
            }  
        } else {
            throw std::logic_error("It is not quadrate");
        }
        
    }

    point center() const override;
    double square() const override;
    void print(std::ostream& os) const override;
};

#endif
