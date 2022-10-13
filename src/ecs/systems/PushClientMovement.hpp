/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** PushClientMovement
*/

#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"

namespace ecs::systems
{
    std::function<void(World &)>  = [](World &world) {
        auto &control = world.registry.getComponents<component::Controllable>();
        auto &position = world.registry.getComponents<component::Position>();

        
    }

} // namespace ecs::systems