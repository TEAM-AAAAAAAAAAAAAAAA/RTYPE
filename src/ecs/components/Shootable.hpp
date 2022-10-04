/*
 * File: Shootable.hpp
 * Project: components
 * File Created: Wednesday, 5th October 2022 12:17:10 am
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Wednesday, 5th October 2022 12:24:17 am
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
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
