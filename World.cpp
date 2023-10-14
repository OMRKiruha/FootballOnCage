#include <fstream>
#include <iostream>
#include <filesystem>


#include "World.h"
#include "Painter.h"


// Длительность одного тика симуляции. Подробнее см. update()
static constexpr double timePerTick = 0.001;


inline std::istream &operator>>(std::istream &is, sf::Color &color) {
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

        // Создаём объект Ball в контейнере World::m_ballsArray
        m_ballsArray.emplace_back(radius, center, velocity, color, isCollidable);
    }

    pointer = Pointer(100, sf::Vector2f(0, 0), sf::Color(255, 0, 0, 0), true);


    if (!m_font.loadFromFile("../data/Arial.ttf")) return;//передаем нашему шрифту файл шрифта
    m_text.setCharacterSize(50); //закидываем в объект текст размер шрифта(в пикселях)
    m_text.setFont(m_font); //закидываем в объект текст шрифт
    m_text.setFillColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
    m_text.setStyle(sf::Text::Bold);//жирный текст
    m_text.setString(L"Hello World");
    m_text.setPosition(1000,1000);
}

/// @brief Отображает состояние мира
void World::show(Painter &painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, sf::Color(255, 255, 255, 255));

    // Вызываем отрисовку каждого шара
    for (const Ball &ball: m_ballsArray) {
        ball.draw(painter);
    }

    // Вызываем отрисовку каждого фейерверка
    for (const Dust &dust: fireworks) {
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

    physics.update(m_ballsArray, fireworks, ticks);
}

void World::removeDust() {
    fireworks.clear();
}

void World::showPointer() {
    pointer.setColor(sf::Color(255, 0, 0, 128));
}

void World::hidePointer() {
    pointer.setColor(sf::Color(255, 0, 0, 0));
}

void World::setPointerXY(sf::Vector2f coord) {
    pointer.setCenter(coord);
}

sf::Text &World::getText() {
    return m_text;
}
