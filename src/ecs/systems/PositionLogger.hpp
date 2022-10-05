#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"

namespace ecs::systems
{
    /**
     * Used to display, as a logger, all the value of the Position & Velocity component
     */
    std::function<void(World &)> positionLogger = [](World &world) {
        auto const &positions = world.registry.getComponents<component::Position>();
        auto const &velocities = world.registry.getComponents<component::Velocity>();

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
