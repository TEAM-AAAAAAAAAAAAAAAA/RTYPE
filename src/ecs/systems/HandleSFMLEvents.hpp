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

        while (world.getWindow().pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: world.getWindow().close(); break;
                case sf::Event::KeyPressed: {
                    // auto const &shootables = world.registry.getComponents<component::Shootable>();

                    // for (size_t i = 0; i < shootables.size(); ++i) {
                        // auto const &shoot = shootables[i];
                        // if (shoot) {
                        //     if (event.key.code == shoot.value().Shoot || event.key.code == shoot.value().ShootSecondary)
                        //         world.pushEvent(ecs::Event(ecs::Event::EventType::Shoot));
                        // }
                    // }
                } break;
                default: break;
            }
        }
#endif
    };
} // namespace ecs::systems
