#pragma once

#include <functional>
#include <iostream>
#include "../../ecs/World.hpp"
#include "../../ecs/components/Position.hpp"
#include "../../ecs/components/Velocity.hpp"

namespace ecs::systems
{
    std::function<void(World &)> movement = [](World &world) {
        auto &positions = world.registry.getComponents<component::Position>();
        auto const &velocities = world.registry.getComponents<component::Velocity>();

        for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
            auto &pos = positions[i];
            auto const &vel = velocities[i];
            if (pos && vel) {
                pos.value().x += vel.value().x;
                pos.value().y += vel.value().y;
            }
        };
    };
}
