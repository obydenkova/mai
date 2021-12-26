#include "factory.h"

std::shared_ptr<figure> factory::FigureCreate(std::istream &is) {
    std::string name;
    is >> name;
    if (name == "square" ) {
        return std::shared_ptr<figure> ( new square(is));
    } else if (name == "rectangle") {
        return std::shared_ptr<figure> ( new rectangle(is));
    } else if (name == "trapezoid") {
        return std::shared_ptr<figure> ( new trapezoid(is));
    } else {
        throw std::logic_error("There is no such figure\n");
    }
}

std::shared_ptr<figure> factory::FigureCreateFile(std::ifstream &is) {
    std::string name;
    is >> name;
    if (name == "square" ) {
        return std::shared_ptr<figure> (new square(is));
    } else if (name == "rectangle") {
        return std::shared_ptr<figure> (new rectangle(is));
    } else if (name == "trapezoid") {
        return std::shared_ptr<figure> (new trapezoid(is));
    } else {
        throw std::logic_error("There is no such figure\n");
    }
}