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
    /**
     * Used to show a red rectangle shape around the entity to display its hitBox
     */
    struct Hitbox {
        explicit Hitbox(sf::Keyboard::Key key) : enableHitBox(false), keyBoardKey(key) {}

        /**
         * Toogle used to know if we need to enable or disable the HitBox
         */
        bool enableHitBox;

        /**
         * The associated binding to show the hitBox
         */
        sf::Keyboard::Key keyBoardKey;

        /**
         * Used to switch the enable/disable mode of the hitBox pressing H
         */
        inline void switchHitBox() { enableHitBox = !enableHitBox;};

        /**
         * Setter of the HitBox class
         */
         inline void setHitBoxKey(sf::Keyboard::Key key) {keyBoardKey = key;};
    };
} // namespace ecs::component
