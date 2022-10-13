/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Draw
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
    /**
     * Used to set the scale, the position and the texture of the entity before display it
     */
    std::function<void(World &)> draw = [](World &world) {
#ifdef CLIENT_COMPILATION_MODE
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
#endif
    };
} // namespace ecs::systems
