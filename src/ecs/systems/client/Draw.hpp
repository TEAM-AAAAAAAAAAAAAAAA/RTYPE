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
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/client/Animated.hpp"
#include "components/client/Drawable.hpp"

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
        auto &animateds = world.registry.getComponents<component::Animated>();

        world.getWindow().clear();
        for (size_t i = 0; i < positions.size() && i < sizes.size() && i < drawables.size(); ++i) {
            auto const &pos = positions[i];
            auto const &size = sizes[i];
            auto const &draw = drawables[i];

            if (pos && size && draw) {
                sf::Sprite sprite;
                float scaleX;
                float scaleY;
                sprite.setTexture(draw.value().Texture);
                if (i < animateds.size() && animateds[i]) {
                    auto &anim = animateds[i];
                    sprite.setTextureRect(sf::IntRect(anim.value().width * anim.value().current + anim.value().origin_x, anim.value().origin_y, anim.value().width, draw.value().Texture.getSize().y));
                    anim.value().cur_freq++;
                    if (anim.value().cur_freq >= anim.value().freq) {
                        anim.value().cur_freq = 0;
                        anim.value().current++;
                        if (anim.value().current * anim.value().width + anim.value().origin_x >= anim.value().max)
                            anim.value().current = 0;
                    }
                    if (static_cast<float>(draw.value().Texture.getSize().x != 0))
                        scaleX = static_cast<float>(size.value().width) / static_cast<float>(anim.value().width);
                    else
                        scaleX = 0;
                    if (static_cast<float>(draw.value().Texture.getSize().y != 0))
                        scaleY = static_cast<float>(size.value().height) / static_cast<float>(draw.value().Texture.getSize().y);
                    else
                        scaleY = 0;
                    scaleY = static_cast<float>(size.value().height) / static_cast<float>(draw.value().Texture.getSize().y);
                } else {
                    if (static_cast<float>(draw.value().Texture.getSize().x != 0))
                        scaleX = static_cast<float>(size.value().width) / static_cast<float>(draw.value().Texture.getSize().x);
                    else
                        scaleX = 0;
                    if (static_cast<float>(draw.value().Texture.getSize().y != 0))
                        scaleY = static_cast<float>(size.value().height) / static_cast<float>(draw.value().Texture.getSize().y);
                    else
                        scaleY = 0;
                }
                sprite.setScale(scaleX, scaleY);
                sprite.setPosition({static_cast<float>(pos.value().x), static_cast<float>(pos.value().y)});
                world.getWindow().draw(sprite);
            }
        };
        world.getWindow().display();
#endif
    };
} // namespace ecs::systems
