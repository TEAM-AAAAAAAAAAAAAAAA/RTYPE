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
#include "Window.hpp"
#include "World.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/client/Animated.hpp"
#include "components/client/Drawable.hpp"
#include "components/client/Hitbox.hpp"

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
        auto const &hitBoxes = world.registry.getComponents<component::Hitbox>();

        utils::Window::getInstance().clear();
        for (size_t i = 0; i < positions.size() && i < sizes.size() && i < drawables.size(); i++) {
            auto const &pos = positions[i];
            auto const &size = sizes[i];
            auto const &draw = drawables[i];
            if (pos && size && draw) {
                sf::Sprite sprite;
                sprite.setTexture(draw.value().getTexture());
                if (i < animations.size() && animations[i]) {
                    sprite.setTextureRect(animations[i].value().getFrameRect());
                } else {
                    sprite.setTextureRect(draw.value().rect);
                }
                float scaleX =
                    static_cast<float>(size.value().width) / static_cast<float>(sprite.getTextureRect().width);
                float scaleY =
                    static_cast<float>(size.value().height) / static_cast<float>(sprite.getTextureRect().height);
                sprite.setScale(scaleX, scaleY);
                sprite.setPosition({static_cast<float>(pos.value().x), static_cast<float>(pos.value().y)});
                // if (draw.value().rotation) {
                //     sprite.setOrigin(size.value().width / 2, size.value().height / 2);
                //     sprite.setRotation(draw.value().rotation);
                // }
                utils::Window::getInstance().draw(sprite);
            }
            if (i < hitBoxes.size()) {
                auto const &hitBox = hitBoxes[i];

                if (hitBox && size && pos) {
                    if (hitBox->enableHitBox) {
                        sf::RectangleShape hitBoxRec({0, 0});

                        hitBoxRec.setFillColor(sf::Color::Transparent);
                        hitBoxRec.setOutlineColor(sf::Color::Red);
                        hitBoxRec.setOutlineThickness(2);
                        hitBoxRec.setSize({(float)size->width, (float)size->height});
                        hitBoxRec.setPosition({(float)(pos->x), (float)(pos->y)});
                        utils::Window::getInstance().draw(hitBoxRec);
                    }
                }
            }
        };
        utils::Window::getInstance().display();
    };
} // namespace ecs::systems
