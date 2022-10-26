/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Drawable
*/

#pragma once

#include "../../../client/AssetLoader.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace ecs::component
{
    /**
     * Drawable component is used to know if the Entity is able to be draw and in which manner
     * It differs by constructor parameters
     */
    struct Drawable {
        Drawable(const std::filesystem::path &texture, sf::IntRect rect) : rect(rect), textureKey(texture) {}
        inline sf::Texture &getTexture() { return asset::AssetLoader::GetTexture(textureKey); }

        inline const sf::Texture &getTexture() const { return asset::AssetLoader::GetTexture(textureKey); }

        std::string textureKey;
        sf::IntRect rect;
    };
} // namespace ecs::component
