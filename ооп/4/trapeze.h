#ifndef D_TRAPEZE_H
#define D_TRAPEZE_H

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cassert>

#include "vertex.h"

template<class T>
struct trapeze {
  vertex<T> vertices[4];

  trapeze(std::istream& is);
    
  vertex<double> center() const;
  double area() const;
  void print(std::ostream& os) const;

};

template<class T>
trapeze<T>::trapeze(std::istream& is) {
  for(int i = 0; i < 4; ++i){
    is >> vertices[i];
  }
  assert(((vertices[1].x - vertices[0].x)*(vertices[3].y - vertices[2].y)) == ((vertices[3].x - vertices[2].x)*(vertices[1].y - vertices[0].y)));
}

template<class T>
vertex<double> trapeze<T>::center() const {
  return {(vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) * 0.25, (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) * 0.25};
}

template<class T>
double trapeze<T>::area() const {
  const double l11 = vertices[1].x - vertices[0].x;
  const double l12 = vertices[1].y - vertices[0].y;
  const double l21 = vertices[3].x - vertices[2].x;
  const double l22 = vertices[3].y - vertices[2].y;
  const double lh = ((vertices[3].x - vertices[0].x)*(vertices[3].x - vertices[2].x)+(vertices[3].y - vertices[0].y)*(vertices[3].y - vertices[2].y))/sqrt((vertices[3].x - vertices[2].x)*(vertices[3].x - vertices[2].x)+(vertices[3].y - vertices[2].y)*(vertices[3].y - vertices[2].y));
  const double h = sqrt((vertices[3].x - vertices[0].x)*(vertices[3].x - vertices[0].x)+(vertices[3].y - vertices[0].y)*(vertices[3].y - vertices[0].y)-lh*lh);
  return ((abs(l11) + abs(l12) + abs(l21) + abs(l22)) * abs(h) * 0.5);
}

template<class T>
void trapeze<T>::print(std::ostream& os) const {
  os << "Trapezoid ";
  for(int i = 0; i < 4; ++i){
    os << "[" << vertices[i] << "]";
    if(i + 1 != 4){
      os << " ";
    }
  }
  os << '\n';
}

#endif // D_TRAPEZE_H_
