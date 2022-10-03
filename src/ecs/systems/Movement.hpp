#pragma once

#include <functional>
#include <iostream>
#include "../../ecs/Registry.hpp"
#include "../../ecs/components/Position.hpp"
#include "../../ecs/components/Velocity.hpp"

namespace ecs::systems
{
    std::function<void(Registry &)> movement = [](Registry &r) {
        auto &positions = r.getComponents<component::Position>();
        auto &velocities = r.getComponents<component::Velocity>();

        for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
            auto &pos = positions[i];
            auto &vel = velocities[i];
            if (pos && vel) {
                pos.value().x += vel.value().x;
                pos.value().y += vel.value().y;

            }
        };
    };
}
