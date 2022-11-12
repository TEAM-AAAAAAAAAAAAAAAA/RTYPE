/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** FollowEntitySystem
*/

#pragma once

#include <functional>
#include "World.hpp"
#include "components/Position.hpp"
#include "components/server/FollowEntity.hpp"

namespace ecs::systems
{
    std::function<void(World &)> followEntitySystem = [](World &world) {
        auto &positions = world.registry.getComponents<component::Position>();
        auto const &follows = world.registry.getComponents<component::FollowEntity>();

        for (std::size_t i = 0; i < positions.size() && i < follows.size(); i++) {
            auto &pos = positions[i];
            auto const &fol = follows[i];

            if (pos && fol) {
                if (fol.value().entityId < positions.size()) {
                    if (positions[fol.value().entityId]) {
                        pos.value().x = positions[fol.value().entityId].value().x - 50;
                        pos.value().y = positions[fol.value().entityId].value().y + 50;
                    }
                }
            }
        }
    };
} // namespace ecs::systems
