/*
** EPITECH PROJECT, by hourcadettej on 10/29/22.
** rtype
** File description:
** rtype
*/

#pragma once

#include "SFML/Window/Keyboard.hpp"

namespace ecs::component
{
    struct Hitbox {
        explicit Hitbox(sf::Keyboard::Key key) : enableHitBox(false), HitBoxKey(key)
        {
        }

        sf::Keyboard::Key HitBoxKey;
        bool enableHitBox;

        inline void switchHitBox() { enableHitBox = !enableHitBox;};
    };
} // namespace ecs::component
