#include "World.h"
#include "Painter.h"
#include <fstream>
#include <iostream>
#include <filesystem>


// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;


inline std::istream& operator>>(std::istream& is, sf::Color& color){
    int16_t red{};
    int16_t green{};
    int16_t blue{};
    int16_t alfa{};
    is >> red >> green >> blue >> alfa;
    color.r = red;
    color.g = green;
    color.b = blue;
    color.a = alfa;
    return is;
}

/**
 * @brief Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(std::string_view worldFilePath) {

    std::ifstream stream(std::filesystem::path(worldFilePath), std::ios::in);
    if (!stream.is_open()) {
        std::cout << "Unable to open WorldFile";
        exit(1);
    }

    stream >> topLeft >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    // Переменные для полей класса
    Point center;
    Point velocity;
    double radius;
    sf::Color color;
    bool isCollidable;

    // Здесь не хватает обработки ошибок, но на текущем
    // уровне прохождения курса нас это устраивает
    while (stream.peek(), stream.good()) {
        // Читаем координаты центра шара (x, y) и вектор его скорости (vx, vy)
        stream >> center >> velocity;

        // Читаем три составляющие цвета шара
        stream >> color;

        // Читаем радиус шара
        stream >> radius;

        // Читаем свойство шара isCollidable, которое указывает, требуется ли
        // обрабатывать пересечение шаров как столкновение, true - требуется.
        stream >> std::boolalpha >> isCollidable;

        // Создаём объект Ball в контейнере World::balls
        balls.emplace_back(radius, center, velocity, color, isCollidable);
    }

    pointer = Ball(100, Point(0,0), Velocity(), sf::Color(0, 0, 0, 0), true );
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, sf::Color(255, 255, 255,255));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }

    // Вызываем отрисовку каждого фейерверка
    for (const Dust& dust : fireworks) {
        dust.draw(painter);
    }

    pointer.draw(painter);
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако компьютеры дискретны по
     * своей природе. Поэтому симуляцию взаимодействия шаров выполняем
     * дискретными "тиками". Т.е. если с момента прошлой симуляции прошло time
     * секунд, time / timePerTick раз обновляем состояние мира. Каждое такое
     * обновление - тик - в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения один шар пересекается
     * с другим или с границей мира.
     * В общем случае время не делится нацело на длительность тика, сохраняем
     * остаток в restTime и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, fireworks, ticks);
}
void World::removeDust() {
    fireworks.clear();
}

void World::showPointer() {
    pointer.setColor(sf::Color(0,0,0,255));
}

void World::hidePointer() {
    pointer.setColor(sf::Color(0,0,0,0));
}

void World::setPointerXY(Point coord) {
    pointer.setCenter(coord);
}
