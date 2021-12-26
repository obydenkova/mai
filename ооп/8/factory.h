#ifndef _D_FACTORY_H_
#define _D_FACTORY_H_

#include <memory>
#include <iostream>
#include <fstream>
#include "figure.h"
#include <string>

struct factory {
    std::shared_ptr<figure> new_figure(std::istream& is);
};

#endif // _D_FACTORY_H_
