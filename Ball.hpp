#pragma once

#include <SFML/Graphics/Color.hpp>
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"


class Ball {
public:
    Ball() = default;

    Ball(double radius, Point center, Velocity velocity, sf::Color color,
         bool isCollidable);

    ~Ball() = default;

    void setVelocity(const Velocity &velocity) { m_velocity = velocity; };
    [[nodiscard]] Velocity getVelocity() const { return {m_velocity}; };

    void draw(Painter &painter) const;

    void setCenter(const Point &center) { m_center = center; };
    [[nodiscard]] Point getCenter() const{ return m_center; };

    [[nodiscard]] double getRadius() const { return m_radius; };

    [[nodiscard]] double getMass() const { return m_mass; };

    static bool isCollidableBalls(Ball &one, Ball &other);

    [[nodiscard]] bool getCollidable() const { return m_isCollidable; };

    void setColor(sf::Color color) { m_color = color; };

private:
    double m_radius{};
    double m_mass{};
    Point m_center;
    Velocity m_velocity;
    sf::Color m_color;
    bool m_isCollidable{};
};
