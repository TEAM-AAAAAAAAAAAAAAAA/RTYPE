/*
 * File: HandleSFMLEvents.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 7:34:35 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Wednesday, 5th October 2022 2:10:39 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include "World.hpp"

namespace ecs::systems
{
    /**
     * Used to manage Sfml events
     * Currently able to manage the following actions:
     * Close the window, KeyPressed
     */
    std::function<void(World &)> handleSFMLEvents = [](World &world) {
        sf::Event event;

        while (world.getWindow().pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: world.getWindow().close(); break;
                case sf::Event::KeyPressed: {
                    auto const &shootables = world.registry.getComponents<component::Shootable>();

                    for (size_t i = 0; i < shootables.size(); ++i) {
                        auto const &shoot = shootables[i];
                        if (shoot) {
                            if (event.key.code == shoot.value().Shoot || event.key.code == shoot.value().ShootSecondary)
                                world.pushEvent(ecs::Event(ecs::Event::EventType::Shoot));
                        }
                    }
                } break;
                default: break;
            }
        }
    };
} // namespace ecs::systems
