#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <memory>
#include <iostream>
#include <fstream>
#include "square.h"
#include "rectangle.h"
#include "trapezoid.h"
#include <string>

struct factory {
    std::shared_ptr<figure> FigureCreate(std::istream& is);
    std::shared_ptr<figure> FigureCreateFile(std::ifstream& is);
};

#endif //_FACTORY_H_
