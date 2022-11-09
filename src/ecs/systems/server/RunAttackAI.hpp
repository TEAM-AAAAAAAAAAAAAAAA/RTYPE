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
#include <vector>

namespace ecs::systems
{
    /**
     * Runs the AIs stored in the enities
     */
    std::function<void(World &)> runAttackAI = [](World &world) {
        auto &attackAIs = world.registry.getComponents<component::AttackAI>();

        using chrono = std::chrono::high_resolution_clock;
        using chronoDuration = std::chrono::duration<double, std::milli>;

        std::vector<std::pair<std::function<void(const std::size_t)>, std::size_t>> aIQueue;

        for (size_t i = 0; i < attackAIs.size(); ++i) {
            auto &atkAI = attackAIs[i];

            if (atkAI) {
                if ((chrono::now().time_since_epoch().count() - atkAI.value().lastAttack) / 10000000
                    > atkAI.value().lastAttackDelay) {
                    auto &nextAtk = atkAI.value().getRandomAttack();
                    std::pair<std::function<void(const std::size_t)>, std::size_t> pair;
                    pair.first = nextAtk._function;
                    pair.second = i;
                    aIQueue.push_back(pair);
                    atkAI.value().lastAttack = chrono::now().time_since_epoch().count();
                    atkAI.value().lastAttackDelay = nextAtk.reloadTime;
                }
            }
        };
        /**
         * @brief Workaround to be able to create entities with AttackAIs while iterating on AttackAI
         * 
         * @param aIQueue 
         */
        for (auto &&ai : aIQueue)
        {
            ai.first(ai.second);
        }
        
    };
} // namespace ecs::systems
