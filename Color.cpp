#include "Color.h"

Color::Color(double red, double green, double blue)
    : r{red}, g{green}, b{blue} {}


void Color::setColor(double red, double green, double blue) {
    this->r = red;
    this->g = green;
    this->b = blue;
}
