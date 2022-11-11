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
#include "components/EntityType.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
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
        auto const &entityTypes = world.registry.getComponents<component::EntityType>();
        auto const &sizes = world.registry.getComponents<component::Size>();

        using chrono = std::chrono::high_resolution_clock;
        using chronoDuration = std::chrono::duration<double, std::milli>;

        static auto clock = chrono::now();
        if (chronoDuration(chrono::now() - clock).count() > 10) {
            for (size_t i = 0; i < positions.size() && i < velocities.size() && i < directions.size(); ++i) {
                auto &pos = positions[i];
                auto const &vel = velocities[i];
                auto &dir = directions[i];

                if (pos && vel && dir) {
                    pos.value().x += vel.value().x * dir.value().x;
                    pos.value().y += vel.value().y * dir.value().y;
                    if (i < entityTypes.size() && entityTypes[i]) {
                        if (entityTypes[i].value().type != component::EntityType::Types::Bullet
                            && entityTypes[i].value().type != component::EntityType::Types::EnergySphere
                            && entityTypes[i].value().type != component::EntityType::Types::Laser
                            && entityTypes[i].value().type != component::EntityType::Types::Rocket
                            && entityTypes[i].value().type != component::EntityType::Types::Asteroid) {
                            if (i < sizes.size()) {
                                if (sizes[i]) {
                                    if (pos.value().x < 0)
                                        pos.value().x = 0;
                                    else if (pos.value().x + sizes[i].value().width > utils::constant::mapWidth)
                                        pos.value().x = utils::constant::mapWidth - sizes[i].value().width;
                                    if (pos.value().y < 0)
                                        pos.value().y = 0;
                                    else if (pos.value().y + sizes[i].value().height > utils::constant::mapHeight)
                                        pos.value().y = utils::constant::mapHeight - sizes[i].value().height;
                                }
                            }
                        }
                    }
                }
            };
            clock = chrono::now();
        }
    };
} // namespace ecs::systems
