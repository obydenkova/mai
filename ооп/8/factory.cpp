#include "factory.h"
#include "square.h"
#include "rectangle.h"
#include "trapezoid.h"

std::shared_ptr<figure> factory::new_figure(std::istream &is) {
    std::string name;
    is >> name;
    if (name == "square") {
        return std::shared_ptr<figure> ( new square(is));
    } else if ( name == "rectangle") {
        return std::shared_ptr<figure> ( new rectangle(is));
    } else if ( name == "trapezoid") {
        return std::shared_ptr<figure> ( new trapezoid(is));
    } else {
        throw std::logic_error("There's no such figure\n");
    }
}


