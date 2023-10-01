#include "Ball.hpp"
#include <cmath>

/**
 * @brief Конструктор от всех параметров
 * @details В нашем приложении считаем, что все шары состоят из одинакового
 * материала с фиксированной плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 **/
Ball::Ball(double radius, Point center, Velocity velocity, sf::Color color,
           bool isCollidable)
    : m_radius(radius), m_mass(0.0), m_center(center), m_velocity(velocity),
      m_color(color), m_isCollidable(isCollidable) {
    m_mass = M_PI * pow(m_radius, 3.) * 4. / 3.;
}


bool Ball::isCollidableBalls(Ball& one, Ball& other) {
    return one.m_isCollidable && other.m_isCollidable;
}


/**
 * @brief Выполняем отрисовку объекта
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(m_center, m_radius, m_color);
}