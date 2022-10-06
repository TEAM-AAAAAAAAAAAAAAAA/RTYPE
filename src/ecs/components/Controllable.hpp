/*
 * File: Controllable.hpp
 * Project: components
 * File Created: Monday, 3rd October 2022 6:17:46 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 7:26:15 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include "SFML/Window/Keyboard.hpp"

namespace ecs::component
{
    /**
     * Controllable component represents all the authorized input for the user
     * In brief, it currently manage the following inputs :
     * Up, Down, Right, Left
     * Secondary Up, Secondary Down, Secondary Left, Secondary Right,
     */
    struct Controllable {
        Controllable(sf::Keyboard::Key moveUp, sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveDown,
            sf::Keyboard::Key moveRight, sf::Keyboard::Key moveUpSecondary = sf::Keyboard::Unknown,
            sf::Keyboard::Key moveLeftSecondary = sf::Keyboard::Unknown,
            sf::Keyboard::Key moveDownSecondary = sf::Keyboard::Unknown,
            sf::Keyboard::Key moveRightSecondary = sf::Keyboard::Unknown)
            : MoveUp(moveUp), MoveLeft(moveLeft), MoveDown(moveDown), MoveRight(moveRight),
              MoveRightSecondary(moveRightSecondary), MoveUpSecondary(moveUpSecondary),
              MoveDownSecondary(moveDownSecondary), MoveLeftSecondary(moveLeftSecondary)
        {
        }

        sf::Keyboard::Key MoveUp;
        sf::Keyboard::Key MoveLeft;
        sf::Keyboard::Key MoveDown;
        sf::Keyboard::Key MoveRight;

        sf::Keyboard::Key MoveUpSecondary;
        sf::Keyboard::Key MoveLeftSecondary;
        sf::Keyboard::Key MoveDownSecondary;
        sf::Keyboard::Key MoveRightSecondary;
    };
} // namespace ecs::component
