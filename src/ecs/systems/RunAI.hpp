/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** RunAI
*/

#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Direction.hpp"
#include "components/EntityAI.hpp"

namespace ecs::systems
{
    /**
     * Runs the AIs stored in the enities
     */
    std::function<void(World &)> runAI = [](World &world) {
        auto &directions = world.registry.getComponents<component::Direction>();
        auto &entityAIs = world.registry.getComponents<component::EntityAI>();

        using chrono = std::chrono::high_resolution_clock;
        using chronoDuration = std::chrono::duration<double, std::milli>;

        static auto clock = chrono::now();
        for (size_t i = 0; i < directions.size() && i < entityAIs.size(); ++i) {
            auto &dir = directions[i];
            auto &ai = entityAIs[i];

            if (dir && ai) {
                if (chronoDuration(chrono::now() - clock).count()
                    > static_cast<size_t>(ai.value().getDelay()) * 1000) {
                    auto &tmpDir = ai.value().getNextDirection();
                    dir.value().x = tmpDir.first;
                    dir.value().y = tmpDir.second;
                    dir.value().hasMoved = true;
                    clock = chrono::now();
                }
            }
        };
    };
} // namespace ecs::systems
