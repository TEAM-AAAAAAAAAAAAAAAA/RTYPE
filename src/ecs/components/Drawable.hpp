/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Drawable
*/

#pragma once

#include "SFML/Graphics/Texture.hpp"

namespace ecs::component
{
    /**
     * Drawable component is used to know if the Entity is able to be draw and in which manner
     * It differs by constructor parameters
     */
    struct Drawable {
        explicit Drawable(const std::string &texture) { Texture.loadFromFile(texture); }
        Drawable(const std::string &texture, sf::IntRect rect) { Texture.loadFromFile(texture, rect); }
        explicit Drawable(const sf::Texture &texture) : Texture(texture) {}

        sf::Texture Texture;
    };
} // namespace ecs::component
