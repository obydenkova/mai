#include <iostream>
#include <tuple>

#include "vertex.h"
#include "square.h"
#include "rectangle.h"
#include "trapeze.h"

#include "templates.h"

void print_help() {

    std::cout << "'1'           - Create square"     << std::endl;
    std::cout << "'2'           - Create rectangle"  << std::endl;
    std::cout << "'3'           - Create trapeze"    << std::endl;
    std::cout << "'4'           - Tuple"             << std::endl;
    std::cout << "'0'           - Exit"              << std::endl;
}

enum Commands{ // перечисление комманд
  cmd_quit,
  cmd_sqr,
  cmd_rect,
  cmd_trpz,
    cmd_tpl
};

template<class T> // шаблон функции process
void process() {
  T object(std::cin);
  //void read(std::cin, object);
  print(object, std::cout);
  std::cout << "Center: [" << center(object) << "]" << std::endl;
  std::cout << "Area: " << area(object) << std::endl;
}


int main(){
  print_help();
  for (;;){
    int command;
    std::cin >> command;
    switch (command){
    case cmd_quit:
      exit(0);
    case cmd_sqr:
      process<square<int>>();
      break;
    case cmd_rect:
      process<rectangle<int>>();
      break;
    case cmd_trpz:
      process<trapeze<int>>();
      break;
    case cmd_tpl:
      vertex<int> vrtx[4];
      for(int i = 0; i < 4; ++i){
	std::cin >> vrtx[i];
      }
      std::tuple<vertex<int>, vertex<int>, vertex<int>, vertex<int>> // кортеж tuple (элементы с фикс размером)
	f_tuple{{vrtx[0].x, vrtx[0].y}, {vrtx[1].x, vrtx[1].y}, {vrtx[2].x, vrtx[2].y}, {vrtx[3].x, vrtx[3].y}};
      if ((((vrtx[1].x - vrtx[0].x)*(vrtx[3].x - vrtx[0].x))+((vrtx[1].y - vrtx[0].y)*(vrtx[3].y - vrtx[0].y)) == 0) && (((vrtx[2].x - vrtx[1].x)*(vrtx[2].x - vrtx[3].x))+((vrtx[2].y - vrtx[1].y)*(vrtx[2].y - vrtx[3].y)) == 0) && (((vrtx[3].x - vrtx[2].x)*(vrtx[1].x - vrtx[2].x))+((vrtx[3].y - vrtx[2].y)*(vrtx[1].y - vrtx[2].y)) == 0)) {
	if (((vrtx[1].x - vrtx[0].x) == (vrtx[0].y - vrtx[3].y)) && ((vrtx[2].x - vrtx[1].x) == (vrtx[1].y - vrtx[0].y)) && ((vrtx[3].x - vrtx[2].x) == (vrtx[2].y - vrtx[1].y))){
	  std::cout << "Tuple (As Square) ";
	} else {
	  std::cout << "Tuple (As Rectangle) ";
	}
      } else if (((vrtx[1].x - vrtx[0].x)*(vrtx[3].y - vrtx[2].y)) == ((vrtx[3].x - vrtx[2].x)*(vrtx[1].y - vrtx[0].y))) {
	std::cout << "Tuple (As Trapezoid) ";
      } else {
	std::cout << "Tuple ";
      } 
      print(f_tuple);
      std::cout << std::endl;
      std::cout << "Center: [" << center(f_tuple) << "]" << std::endl;
      std::cout << "Area: " << area(f_tuple) << std::endl;
    }
  }
}
