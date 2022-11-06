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
        explicit Hitbox() : enableHitBox(false){}

        /**
         * Toogle used to know if we need to enable or disable the HitBox
         */
        bool enableHitBox;

        /**
         * Used to switch the enable/disable mode of the hitBox pressing H
         */
        inline void switchHitBox() { enableHitBox = !enableHitBox;};

    };
} // namespace ecs::component
