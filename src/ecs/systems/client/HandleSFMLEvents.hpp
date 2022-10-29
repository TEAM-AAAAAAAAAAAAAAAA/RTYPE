/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleSFMLEvents
*/

#pragma once

#include <functional>
#include "World.hpp"

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
#ifdef CLIENT_COMPILATION_MODE
        sf::Event event;

        while (world.getWindow().pollEvent(event))
            if (event.type == sf::Event::Closed)
                world.getWindow().close();
#endif
    };
} // namespace ecs::systems