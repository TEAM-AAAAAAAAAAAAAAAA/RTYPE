/*
 * File: HandleSFMLEvents.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 7:34:35 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 10:11:59 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Controllable.hpp"

namespace ecs::systems
{
    std::function<void(World &)> handleSFMLEvents = [](World &world) {
        sf::Event event;
        auto const &controllables = world.registry.getComponents<component::Controllable>();

        for (size_t i = 0; i < controllables.size(); ++i) {
            auto &contr = controllables[i];

            if (contr) {
                auto const con = contr.value();
                while (world.getWindow().pollEvent(event)) {
                    switch (event.type) {
                        case sf::Event::Closed: world.getWindow().close(); break;
                        case sf::Event::KeyPressed: break;
                        default: break;
                    }
                }
            }
        }
    };
}
