/*
 * File: Movement.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 6:33:43 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Wednesday, 5th October 2022 2:08:02 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Direction.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"

namespace ecs::systems
{
    /**
     * Used to apply the values of the velocity component to the position component according to the internal clock of
     * the system
     */
    std::function<void(World &)> movement = [](World &world) {
        auto &positions = world.registry.getComponents<component::Position>();
        auto const &velocities = world.registry.getComponents<component::Velocity>();
        auto &directions = world.registry.getComponents<component::Direction>();

        static sf::Clock clock;
        for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
            auto &pos = positions[i];
            auto const &vel = velocities[i];
            auto &dir = directions[i];
            if (pos && vel) {
                if (clock.getElapsedTime().asMilliseconds() > 10) {
                    pos.value().x += vel.value().x * (dir.value().x);
                    pos.value().y += vel.value().y * dir.value().y;
                    clock.restart();
                    dir.value().x = 0;
                    dir.value().y = 0;
                }
            }
        };
    };
} // namespace ecs::systems