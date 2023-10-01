#pragma once
#include "View.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <chrono>
#include <memory>

class World;

class Application {
  public:
    Application(std::string_view name);
    void run(World& world);

  private:
    void processEvents(World& world);
    void updateWorld(World& world);
    void drawWorld(const World& world);

  private:
    sf::RenderWindow window;
    View view;
    std::chrono::system_clock::time_point time;
    double totalTime{};
};
