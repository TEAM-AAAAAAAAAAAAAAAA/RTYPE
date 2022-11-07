/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** RunAttackAI
*/

#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Direction.hpp"
#include "components/server/AttackAI.hpp"

namespace ecs::systems
{
    /**
     * Runs the AIs stored in the enities
     */
    std::function<void(World &)> runAttackAI = [](World &world) {
        auto &attackAIs = world.registry.getComponents<component::AttackAI>();

        using chrono = std::chrono::high_resolution_clock;
        using chronoDuration = std::chrono::duration<double, std::milli>;

        static auto clock = chrono::now();
        for (size_t i = 0; i < attackAIs.size(); ++i) {
            auto &atkAI = attackAIs[i];

            if (atkAI) {
                if (chronoDuration(chrono::now() - clock).count() - atkAI.value().lastAttack
                    > atkAI.value().lastAttackDelay) {
                    auto &nextAtk = atkAI.value().getRandomAttack();
                    nextAtk.run(i);
                    atkAI.value().lastAttack = chronoDuration(chrono::now() - clock).count();
                    atkAI.value().lastAttackDelay = nextAtk.reloadTime;
                    clock = chrono::now();
                }
            }
        };
    };
} // namespace ecs::systems
