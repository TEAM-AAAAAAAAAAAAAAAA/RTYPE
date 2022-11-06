/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** RunMovementAI
*/

#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Direction.hpp"
#include "components/MovementAI.hpp"

namespace ecs::systems
{
    /**
     * Runs the AIs stored in the enities
     */
    std::function<void(World &)> runMovementAI = [](World &world) {
        auto &directions = world.registry.getComponents<component::Direction>();
        auto &movementAIs = world.registry.getComponents<component::MovementAI>();

        using chrono = std::chrono::high_resolution_clock;
        using chronoDuration = std::chrono::duration<double, std::milli>;

        static auto clock = chrono::now();
        for (size_t i = 0; i < directions.size() && i < movementAIs.size(); ++i) {
            auto &dir = directions[i];
            auto &movAI = movementAIs[i];

            if (dir && movAI) {
                if (chronoDuration(chrono::now() - clock).count()
                    > static_cast<size_t>(movAI.value().getDelay()) * 1000) {
                    auto &tmpDir = movAI.value().getNextDirection();
                    dir.value().x = tmpDir.first;
                    dir.value().y = tmpDir.second;
                    dir.value().hasMoved = true;
                    clock = chrono::now();
                }
            }
        };
    };
} // namespace ecs::systems
