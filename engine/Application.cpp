
#include <chrono>

#include <SFML/Window/Event.hpp>

#include "../World.h"
#include "Application.h"


Application::Application(std::string_view name)
    : window{{3840u, 2160u},
             name.data(),
             sf::Style::Titlebar | sf::Style::Close,
             sf::ContextSettings(0, 0, 4)},
      view({0., 0.}, 1980, 1080, 0.2) {}

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
                world.setPointerXY(sf::Vector2f(event.touch.x, event.touch.y));
                break;
            case sf::Event::EventType::TouchEnded:
                world.hidePointer();
                break;
            case sf::Event::EventType::MouseButtonPressed:
                world.showPointer();
                break;
            case sf::Event::EventType::MouseMoved:
                world.setPointerXY(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                world.m_text.setPosition(event.mouseMove.x, event.mouseMove.y);
                window.draw(world.m_text);
                break;
            case sf::Event::EventType::MouseButtonReleased:
                world.hidePointer();
                break;
            case sf::Event::EventType::MouseWheelScrolled:
                view.onZoom(event.mouseWheelScroll.delta);
                break;
            case sf::Event::Resized:
                break;
            case sf::Event::LostFocus:
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::TextEntered:
                break;
            case sf::Event::KeyPressed:
                break;
            case sf::Event::KeyReleased:
                break;
            case sf::Event::MouseWheelMoved:
                break;
            case sf::Event::MouseEntered:
                break;
            case sf::Event::MouseLeft:
                break;
            case sf::Event::JoystickButtonPressed:
                break;
            case sf::Event::JoystickButtonReleased:
                break;
            case sf::Event::JoystickMoved:
                break;
            case sf::Event::JoystickConnected:
                break;
            case sf::Event::JoystickDisconnected:
                break;
            case sf::Event::SensorChanged:
                break;
            case sf::Event::Count:
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
    window.draw(world.m_text);
}
