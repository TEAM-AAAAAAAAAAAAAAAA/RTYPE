/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Draw
*/

#pragma once

#include <functional>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "World.hpp"
#include "components/Dead.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/client/Animated.hpp"
#include "components/client/Drawable.hpp"

namespace ecs::systems
{
    std::function<void(World &)> Animate = [](World &world) {
        auto const &deads = world.registry.getComponents<component::Dead>();
        auto &animateds = world.registry.getComponents<component::Animated>();

        using chrono = std::chrono::high_resolution_clock;
        using chronoDuration = std::chrono::duration<double, std::milli>;
        for (size_t i = 0; i < animateds.size(); ++i) {
            if (i < deads.size() && deads[i])
                continue;
            auto &anim = animateds[i];

            if (anim) {
                if (chrono::now().time_since_epoch().count() - anim.value().lastSwitch
                    > anim.value().getFrame().delay) {
                    anim.value().nextFrame();
                    anim.value().lastSwitch = chrono::now().time_since_epoch().count();
                }
            }
        }
    };
} // namespace ecs::systems
