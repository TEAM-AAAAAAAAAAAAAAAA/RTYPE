/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleSFMLEvents
*/

#pragma once

#include <functional>
#include "World.hpp"
#include "Window.hpp"

namespace ecs::systems
{
    /**
     * Used to manage Sfml events
     * Currently able to manage the following actions:
     * Close the window
     * KeyPressed, in this case, we check if the bind is known from sfml:
     * if yes, we had it on world's events' stack, nothing otherwise
     */
    std::function<void(World &)> handleSFMLEvents = [](World &world) {
        sf::Event event;

        while (utils::Window::get().pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: utils::Window::get().close(); break;
                case sf::Event::KeyPressed: {
                } break;
                default: break;
            }
        }
    };
} // namespace ecs::systems
