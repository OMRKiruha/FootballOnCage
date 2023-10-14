//
// Created by Professional on 14.10.2023.
//

#pragma once

#include <SFML/Graphics/Color.hpp>
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"


class Pointer {
public:
    Pointer() = default;

    Pointer(double radius, sf::Vector2f center, sf::Color color, bool isCollidable);

    ~Pointer() = default;

    void draw(Painter &painter) const;

    void setCenter(const sf::Vector2f &center) {
        m_center = center;
    };

    [[nodiscard]] bool getCollidable() const { return m_isCollidable; };

    void setColor(sf::Color color) { m_color = color; };

private:
    double m_radius{100};
    sf::Vector2f m_center{};
    sf::Color m_color;
    bool m_isCollidable{};
};
