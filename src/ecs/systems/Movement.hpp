/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Movement
*/

#pragma once

#include <chrono>
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
#ifdef CLIENT_COMPILATION_MODE
        auto const &controllables = world.registry.getComponents<component::Controllable>();
#endif
        using chrono = std::chrono::high_resolution_clock;
        using chronoDuration = std::chrono::duration<double, std::milli>;

        static auto clock = chrono::now();
        if (chronoDuration(chrono::now() - clock).count() > 10) {
            for (size_t i = 0; i < positions.size() && i < velocities.size() && i < directions.size(); ++i) {
                auto &pos = positions[i];
                auto const &vel = velocities[i];
                auto &dir = directions[i];
#ifdef CLIENT_COMPILATION_MODE
                auto const &contr = controllables[i];
#endif

                if (pos && vel && dir) {
                    pos.value().x += vel.value().x * dir.value().x;
                    pos.value().y += vel.value().y * dir.value().y;

#ifdef CLIENT_COMPILATION_MODE
                    if (i < controllables.size() && contr) {
                        dir.value().x = 0;
                        dir.value().y = 0;
                    }
#endif
                }
            };
            clock = chrono::now();
        }
    };
} // namespace ecs::systems
