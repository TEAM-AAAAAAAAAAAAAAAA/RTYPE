#pragma once

#include "SFML/Window/Keyboard.hpp"

namespace ecs::component
{
    struct Controllable {
        Controllable(sf::Keyboard::Key moveUp, sf::Keyboard::Key moveDown, sf::Keyboard::Key moveLeft,
            sf::Keyboard::Key moveRight)
            : MoveUp(moveUp), MoveDown(moveDown), MoveLeft(moveLeft), MoveRight(moveRight)
        {
        }

        sf::Keyboard::Key MoveUp;
        sf::Keyboard::Key MoveDown;
        sf::Keyboard::Key MoveLeft;
        sf::Keyboard::Key MoveRight;
    };
} // namespace ecs::component
