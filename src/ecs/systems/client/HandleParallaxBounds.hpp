/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleParallaxBounds
*/

#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/client/Parallax.hpp"
#include "components/Position.hpp"

namespace ecs::systems
{
    std::function<void(World &)> HandleParallaxBounds = [](World &world) {
        auto &parallaxes = world.registry.getComponents<component::Parallax>();
        auto &positions = world.registry.getComponents<component::Position>();

        for (size_t i = 0; i < parallaxes.size() && i < positions.size(); i++) {
            if (!parallaxes[i] || !positions[i])
                continue;
            if (positions[i].value().x < parallaxes[i].value().threshold) {
                positions[i].value().x += parallaxes[i].value().position;
            }
        }
    };
}
