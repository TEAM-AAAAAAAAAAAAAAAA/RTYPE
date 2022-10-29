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
#include "components/client/Drawable.hpp"
#include "components/client/HitBox.hpp"
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
        auto const &hitBoxes = world.registry.getComponents<component::Hitbox>();

        world.getWindow().clear();
        for (size_t i = 0; i < positions.size() && i < sizes.size() && i < drawables.size(); ++i) {
            auto const &pos = positions[i];
            auto const &size = sizes[i];
            auto const &draw = drawables[i];
            auto const &hitBox = hitBoxes[i];
            if (pos && size && draw) {
                sf::Sprite sprite;
                sprite.setTexture(draw.value().Texture);
                float scaleX = static_cast<float>(size.value().width) / static_cast<float>(draw.value().Texture.getSize().x);
                float scaleY = static_cast<float>(size.value().height) / static_cast<float>(draw.value().Texture.getSize().y);
                sprite.setScale(scaleX, scaleY);
                sprite.setPosition({static_cast<float>(pos.value().x), static_cast<float>(pos.value().y)});
                world.getWindow().draw(sprite);
            }
            if (hitBox && hitBox->enableHitBox) {
                sf::RectangleShape hitBoxRec({0, 0});

                hitBoxRec.setFillColor(sf::Color::Transparent);
                hitBoxRec.setOutlineColor(sf::Color::Red);
                hitBoxRec.setOutlineThickness(2);
                hitBoxRec.setSize({(float)size->width, (float)size->height});
                hitBoxRec.setPosition({(float)(positions[i]->x), (float)(positions[i]->y)});
                world.getWindow().draw(hitBoxRec);
            }
        };
        world.getWindow().display();
#endif
    };
} // namespace ecs::systems
