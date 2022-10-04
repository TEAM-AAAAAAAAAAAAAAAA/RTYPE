/*
 * File: Draw.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 6:33:43 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 7:27:06 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Drawable.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"

namespace ecs::systems
{
    std::function<void(World &)> draw = [](World &world) {
        auto const &positions = world.registry.getComponents<component::Position>();
        auto const &sizes = world.registry.getComponents<component::Size>();
        auto const &drawables = world.registry.getComponents<component::Drawable>();

        world.getWindow().clear();
        for (size_t i = 0; i < positions.size() && i < sizes.size() && i < drawables.size(); ++i) {
            auto const &pos = positions[i];
            auto const &size = sizes[i];
            auto const &draw = drawables[i];
            if (pos && size && draw) {
                sf::Sprite sprite;
                sprite.setScale({float(size.value().width), float(size.value().height)});
                sprite.setPosition({float(pos.value().x), float(pos.value().y)});
                sprite.setTexture(draw.value().Texture);
                world.getWindow().draw(sprite);
            }
        };
        world.getWindow().display();
    };
}