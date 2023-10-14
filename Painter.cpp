
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <algorithm>

#include "Painter.h"


Painter::Painter(sf::RenderWindow &window, const View &view)
        : window{window}, view{view} {
    window.clear();
}

Painter::~Painter() {
    window.display();
}


/**
 * Рисует круг цвета color
 * @param center центр круга
 * @param radius радиус круга
 * @param color цвет заливки
 */
void Painter::draw(const Point &center, double radius, const sf::Color &color) {
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


/**
 * Рисует круглый указатель курсора цвета color
 * @param center центр круга
 * @param radius радиус круга
 * @param color цвет заливки
 */
void Painter::draw(const sf::Vector2f &pos, double radius, const sf::Color &color) {

    const float scaledRadius = float(radius * view.scale());
    // Эмпирическая формула. При таком количестве точек получаем гладкие
    // окружности
    const size_t pointsCount = std::max(int(scaledRadius / 2), 20);

    sf::CircleShape shape(scaledRadius, pointsCount);
    shape.setPosition(sf::Vector2f(pos.x - scaledRadius, pos.y - scaledRadius));
    shape.setFillColor(color);

    window.draw(shape);
}


/**
 * Рисует прямоугольник цвета color
 * @param topLeft координата верхнего левого угла
 * @param bottomRight координата нижнего правого угла
 * @param color цвет заливки
 */
void Painter::draw(const Point &topLeft, const Point &bottomRight,
                   const sf::Color &color) {
    const sf::Vector2f tl = toVector(view.toScreen(topLeft));
    const sf::Vector2f br = toVector(view.toScreen(bottomRight));

    sf::RectangleShape rect(br - tl);
    rect.setPosition(tl);
    rect.setFillColor(color);

    window.draw(rect);
}

sf::Vector2f Painter::toVector(const Point &point) {
    return {float(point.x), float(point.y)};
}