/*
 * File: HandleSFMLEvents.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 7:34:35 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 10:24:43 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include "World.hpp"
#include "components/Controllable.hpp"

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
                case sf::Event::KeyPressed: break;
                default: break;
            }
        }
    };
}
