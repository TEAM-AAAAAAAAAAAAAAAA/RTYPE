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

#ifdef CLIENT_COMPILATION_MODE
    #include "SFML/Graphics.hpp"
#endif

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

        for (size_t i = 0; i < positions.size() && i < sizes.size() && i < drawables.size(); ++i) {
            auto const &pos = positions[i];
            auto const &size = sizes[i];
            auto const &draw = drawables[i];
            if (pos && size && draw) {
                sf::Sprite sprite;
                sprite.setTexture(draw.value().Texture);
                sprite.setScale({float(size.value().width / draw.value().Texture.getSize().x), float(size.value().height / draw.value().Texture.getSize().y)});
                sprite.setPosition({float(pos.value().x), float(pos.value().y)});
                world.getWindow().draw(sprite);
            }
        };
        world.getWindow().display();
        world.getWindow().clear ();
#endif
    };
} // namespace ecs::systems
