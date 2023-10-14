#pragma once

#include <list>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Ball.hpp"
#include "Dust.h"
#include "Physics.h"
#include "Pointer.h"

class Painter;

class World {
  public:
    World(std::string_view worldFilePath);
    void show(Painter& painter) const;
    void update(double time);
    void removeDust();
    void showPointer();
    void hidePointer();
    void setPointerXY(sf::Vector2f coord);
    sf::Text& getText();

  private:
    // Границы мира заданы углами прямоугольника
    Point topLeft{};
    Point bottomRight{};

    // Объект физического движка
    Physics physics{};

    // Контейнер с шарами
    std::vector<Ball> m_ballsArray{};

    // Контейнер со вспышками
    std::list<Dust> fireworks{};

    // Объект указателя мыши или пальца
    Pointer pointer;
public:
    sf::Font m_font;//шрифт
    sf::Text m_text;
    // Длина отрезка времени, который не был
    // учтен при прошлой симуляции. См. реализацию update
    double restTime{0.0};
};
