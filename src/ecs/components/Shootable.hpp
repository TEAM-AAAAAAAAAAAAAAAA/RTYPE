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
    struct Shootable {
        Shootable(sf::Keyboard::Key shoot, sf::Keyboard::Key shootSecondary = sf::Keyboard::Key::Unknown)
            : Shoot(shoot), ShootSecondary(shootSecondary)
        {
        }

        sf::Keyboard::Key Shoot;

        sf::Keyboard::Key ShootSecondary;
    };
} // namespace ecs::component
