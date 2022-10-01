#pragma once

#include "SFML/Window/Keyboard.hpp"

struct InputMoveUp
{
    InputMoveUp(sf::Keyboard::Key input) : Key(input) {}

    sf::Keyboard::Key Key;
};
