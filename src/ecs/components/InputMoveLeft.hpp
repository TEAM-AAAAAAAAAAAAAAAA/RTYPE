#pragma once

#include "SFML/Window/Keyboard.hpp"

namespace ecs::component
{
    struct InputMoveLeft {
        InputMoveLeft(sf::Keyboard::Key input) : Key(input) {}

        sf::Keyboard::Key Key;
    };
} // namespace ecs::component
