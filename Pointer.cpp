//
// Created by Professional on 14.10.2023.
//

#include "Pointer.h"


/**
 * @brief Конструктор от всех параметров
 * @details В нашем приложении считаем, что все шары состоят из одинакового
 * материала с фиксированной плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 **/
Pointer::Pointer(double radius, sf::Vector2f center, sf::Color color, bool isCollidable)
        : m_radius(radius), m_center(center),
          m_color(color), m_isCollidable(isCollidable) {}


/**
 * @brief Выполняем отрисовку объекта
 * @param painter контекст отрисовки
 */
void Pointer::draw(Painter &painter) const {
    painter.draw(m_center, m_radius, m_color);
}