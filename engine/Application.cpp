
#include <chrono>

#include <SFML/Window/Event.hpp>

#include "../World.h"
#include "Application.h"


Application::Application(std::string_view name)
    : window{{1280u, 960u},
             name.data(),
             sf::Style::Titlebar | sf::Style::Close,
             sf::ContextSettings(0, 0, 4)},
      view({0., 0.}, 1280, 960, 0.2) {}

void Application::run(World& world) {
    time = std::chrono::system_clock::now();
    totalTime = 0.;

    while (window.isOpen()) {
        processEvents(world);
        updateWorld(world);
        drawWorld(world);
    }
}

void Application::processEvents(World& world) {
    for (sf::Event event{}; window.pollEvent(event); /**/) {
        switch (event.type) {
            case sf::Event::EventType::Closed:
                window.close();
                break;
            case sf::Event::EventType::TouchBegan:
                world.showPointer();
                break;
            case sf::Event::EventType::TouchMoved:
                world.setPointerXY(Point(event.touch.x, event.touch.y));
                break;
            case sf::Event::EventType::TouchEnded:
                world.hidePointer();
                break;
            case sf::Event::EventType::MouseButtonPressed:
                world.showPointer();
                break;
            case sf::Event::EventType::MouseMoved:
                world.setPointerXY(Point(event.mouseMove.x, -event.mouseMove.y));
                break;
            case sf::Event::EventType::MouseButtonReleased:
                world.hidePointer();
                break;
            case sf::Event::EventType::MouseWheelScrolled:
                view.onZoom(event.mouseWheelScroll.delta);
                break;
        }

    }
}

void Application::updateWorld(World& world) {
    const auto currentTime = std::chrono::system_clock::now();
    const double delta =
        std::chrono::duration_cast<std::chrono::duration<double>>(currentTime -
                                                                  time).count();
    time = currentTime;

    totalTime += delta;

    if (totalTime < 10.) {
        world.update(delta);
    }else {
        world.removeDust();
    }
}

void Application::drawWorld(const World& world) {
    Painter painter(window, view);
    world.show(painter);
}
