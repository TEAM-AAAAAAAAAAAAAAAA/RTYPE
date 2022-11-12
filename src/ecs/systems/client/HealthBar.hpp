/*
** EPITECH PROJECT, by hourcadettej on 11/11/22.
** rtype
** File description:
** rtype
*/

#pragma once

#include <functional>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/client/Animated.hpp"
#include "components/client/Drawable.hpp"
#include "components/client/Hitbox.hpp"
#include "components/client/Text.hpp"
#include "components/Health.hpp"

namespace ecs::systems
{
    std::function<void(World &)> healthBar = [](World &world) {

        auto const &positions = world.registry.getComponents<component::Position>();
        auto &sizes = world.registry.getComponents<component::Size>();
        auto const &healths = world.registry.getComponents<component::Health>();

        for (size_t i = 0; i < positions.size() && i < sizes.size() && i < healths.size(); i++) {
            auto const &pos = positions[i];
            auto &size = sizes[i];
            auto const &health = healths[i];

            if (pos && size && health) {
                if (health->health >= 0 && health->health < utils::constant::maxPlayerHealth) {
                    size.value().width = utils::constant::sizeHealthBar * health->health / 100;
                } else if (health->health < 0)
                    size.value().width = 0;
                else
                    size.value().width = utils::constant::sizeHealthBar;
            }

        }
    };
};