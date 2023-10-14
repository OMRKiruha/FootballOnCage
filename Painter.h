#pragma once

#include <memory>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "engine/View.h"
#include "Point.h"


class View;

namespace sf {
    class RenderWindow;
}

class Painter {
public:
    Painter(sf::RenderWindow &window, const View &view);

    ~Painter();

    void draw(const Point &center, double radius, const sf::Color &color);

    void draw(const sf::Vector2f &pos, double radius, const sf::Color &color);

    void draw(const Point &topLeft, const Point &bottomRight, const sf::Color &color);

private:
    static sf::Vector2f toVector(const Point &point);

private:
    sf::RenderWindow &window;
    const View &view;
};