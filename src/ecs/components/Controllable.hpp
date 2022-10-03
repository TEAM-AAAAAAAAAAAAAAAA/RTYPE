#pragma once

#include "SFML/Window/Keyboard.hpp"

namespace ecs::component
{
    struct Controllable {
        Controllable(sf::Keyboard::Key moveUp, sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveDown,
            sf::Keyboard::Key moveRight)
            : MoveUp(moveUp), MoveLeft(moveLeft), MoveDown(moveDown), MoveRight(moveRight)
        {
        }

        sf::Keyboard::Key MoveUp;
        sf::Keyboard::Key MoveLeft;
        sf::Keyboard::Key MoveDown;
        sf::Keyboard::Key MoveRight;
    };
} // namespace ecs::component
