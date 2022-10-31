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
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/client/Drawable.hpp"

namespace ecs::systems
{
    /**
     * Used to set the scale, the position and the texture of the entity before display it
     */
    std::function<void(World &)> draw = [](World &world) {
        auto const &positions = world.registry.getComponents<component::Position>();
        auto const &sizes = world.registry.getComponents<component::Size>();
        auto const &drawables = world.registry.getComponents<component::Drawable>();
        auto const &animations = world.registry.getComponents<component::Animated>();

        world.getWindow().clear();
        for (size_t i = 0; i < positions.size() && i < sizes.size() && i < drawables.size(); i++) {
            auto const &pos = positions[i];
            auto const &size = sizes[i];
            auto const &draw = drawables[i];
            if (pos && size && draw) {
                sf::Sprite sprite;
                sprite.setTexture(draw.value().getTexture());
                if (i < animations.size() && animations[i])
                    sprite.setTextureRect(animations[i].value().getFrameRect());
                else
                    sprite.setTextureRect(draw.value().rect);
                float scaleX =
                    static_cast<float>(size.value().width) / static_cast<float>(sprite.getTextureRect().width);
                float scaleY =
                    static_cast<float>(size.value().height) / static_cast<float>(sprite.getTextureRect().height);
                sprite.setScale(scaleX, scaleY);
                sprite.setPosition({static_cast<float>(pos.value().x), static_cast<float>(pos.value().y)});
                world.getWindow().draw(sprite);
            }
        };
        world.getWindow().display();
    };
} // namespace ecs::systems
