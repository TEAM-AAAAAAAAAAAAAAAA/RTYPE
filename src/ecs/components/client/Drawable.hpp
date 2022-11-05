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
        /**
         * @brief Construct a new Drawable object with the full texture
         *
         * @param texture the texture key
         */
        Drawable(const std::string &key, float rotation = 0.0) : textureKey(key), rotation(rotation)
        {
            sf::Vector2u size = asset::AssetLoader::GetTexture(key).getSize();
            rect = {0, 0, static_cast<int>(size.x), static_cast<int>(size.y)};
        }

        /**
         * @brief Construct a new Drawable object
         *
         * @param texture the texture key
         * @param rect the rect to use from the texture
         */
        Drawable(const std::string &key, sf::IntRect rect, float rotation = 0.0)
            : rect(rect), textureKey(key), rotation(rotation)
        {
        }

        inline sf::Texture &getTexture() { return asset::AssetLoader::GetTexture(textureKey); }

        inline const sf::Texture &getTexture() const { return asset::AssetLoader::GetTexture(textureKey); }

        std::string textureKey;
        sf::IntRect rect;
        float rotation;
    };
} // namespace ecs::component
