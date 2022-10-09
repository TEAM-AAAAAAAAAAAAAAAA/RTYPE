/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Shootable
*/

#pragma once

#include "SFML/Window/Keyboard.hpp"

namespace ecs::component
{
    /**
     * Shootable component define if the entity is able to shoot on other entities. In brief if it can damage another one
     */
    struct Shootable {
        /**
         * Default constructor of the component,
         * @param shoot Primary shoot sfml key
         * @param shootSecondary Secondary shoot sfml key, unknown as default
         */
        explicit Shootable(sf::Keyboard::Key shoot, sf::Keyboard::Key shootSecondary = sf::Keyboard::Key::Unknown)
            : Shoot(shoot), ShootSecondary(shootSecondary)
        {
        }

        sf::Keyboard::Key Shoot;

        sf::Keyboard::Key ShootSecondary;
    };
} // namespace ecs::component
