#include "PainterImpl.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>

PainterImpl::PainterImpl(sf::RenderWindow& window, const View& view)
    : window{window}, view{view} {
    window.clear();
}

PainterImpl::~PainterImpl() {
    window.display();
}

void PainterImpl::draw(const Point& center, double radius, const sf::Color &color) {
    const sf::Vector2f pos = toVector(view.toScreen(center));
    const float scaledRadius = float(radius * view.scale());
    // Эмпирическая формула. При таком количестве точек получаем гладкие
    // окружности
    const size_t pointsCount = std::max(int(scaledRadius / 2), 20);

    sf::CircleShape shape(scaledRadius, pointsCount);
    shape.setPosition(pos - sf::Vector2f{scaledRadius, scaledRadius});
    shape.setFillColor(color);

    window.draw(shape);
}

void PainterImpl::draw(const Point& topLeft, const Point& bottomRight,
                       const sf::Color &color) {
    const sf::Vector2f tl = toVector(view.toScreen(topLeft));
    const sf::Vector2f br = toVector(view.toScreen(bottomRight));

    sf::RectangleShape rect(br - tl);
    rect.setPosition(tl);
    rect.setFillColor(color);

    window.draw(rect);
}


sf::Vector2f PainterImpl::toVector(const Point& point) const {
    return {float(point.x), float(point.y)};
}
