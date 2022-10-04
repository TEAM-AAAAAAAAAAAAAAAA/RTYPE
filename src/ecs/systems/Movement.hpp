/*
 * File: Movement.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 6:33:43 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 7:27:10 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"

namespace ecs::systems
{
    std::function<void(World &)> movement = [](World &world) {
        auto &positions = world.registry.getComponents<component::Position>();
        auto const &velocities = world.registry.getComponents<component::Velocity>();

        static sf::Clock clock;
        for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
            auto &pos = positions[i];
            auto const &vel = velocities[i];
            if (pos && vel) {
                if (clock.getElapsedTime().asMilliseconds() > 50) {
                    pos.value().x += vel.value().x;
                    pos.value().y += vel.value().y;
                    clock.restart();
                }
            }
        };
    };
}
