
#include <SFML/Graphics/RenderWindow.hpp>

#include "engine/PainterImpl.h"

#include "Painter.h"



Painter::Painter(sf::RenderWindow& window, const View& view)
    : impl{new PainterImpl(window, view)} {}

Painter::~Painter() = default;

void Painter::draw(const Point& center, double radius, const sf::Color &color) {
    impl->draw(center, radius, color);
}

void Painter::draw(const Point& topLeft, const Point& bottomRight,
                   const sf::Color &color) {
    impl->draw(topLeft, bottomRight, color);
}
