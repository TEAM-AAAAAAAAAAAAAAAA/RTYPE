#pragma once

#include <functional>
#include <iostream>
#include "../../ecs/Registry.hpp"
#include "../../ecs/components/Position.hpp"
#include "../../ecs/components/Velocity.hpp"

namespace ecs::systems
{
    std::function<void(Registry &)> positionLogger = [](Registry &r) {
        auto const &positions = r.getComponents<component::Position>();
        auto const &velocities = r.getComponents<component::Velocity>();

        for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
            auto const &pos = positions[i];
            auto const &vel = velocities[i];
            if (pos && vel) {
                std ::cerr << i << ": Position = { " << pos.value().x << ", " << pos.value().y << " }, Velocity = { "
                           << vel.value().x << ", " << vel.value().y << " } " << std ::endl;
            }
        };
    };
}
