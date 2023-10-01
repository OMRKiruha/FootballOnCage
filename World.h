#pragma once

#include <list>
#include <vector>

#include "Ball.hpp"
#include "Dust.h"
#include "Physics.h"

class Painter;

class World {
  public:
    World(std::string_view worldFilePath);
    void show(Painter& painter) const;
    void update(double time);
    void removeDust();
    void showPointer();
    void hidePointer();
    void setPointerXY(Point coord);

  private:
    // Границы мира заданы углами прямоугольника
    Point topLeft{};
    Point bottomRight{};

    // Объект физического движка
    Physics physics{};

    // Контейнер с шарами
    std::vector<Ball> balls{};

    // Контейнер со вспышками
    std::list<Dust> fireworks{};

    // Объект указателя мыши или пальца
    Ball pointer;

    // Длина отрезка времени, который не был
    // учтен при прошлой симуляции. См. реализацию update
    double restTime{0.0};
};
