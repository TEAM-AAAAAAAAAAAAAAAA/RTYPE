/*
 * File: Drawable.hpp
 * Project: components
 * File Created: Monday, 3rd October 2022 6:32:42 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 7:22:28 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include "SFML/Graphics/Texture.hpp"

namespace ecs::component
{
    struct Drawable {
        Drawable(std::string texture) { Texture.loadFromFile(texture); }
        Drawable(std::string texture, sf::IntRect rect) { Texture.loadFromFile(texture, rect); }
        Drawable(sf::Texture texture) : Texture(texture) {}

        sf::Texture Texture;
    };
} // namespace ecs::component
