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
        Drawable(const std::string &key, float rotation = 0.0, bool isActivated = true, bool isButton = false) : textureKey(key), rotation(rotation), activated(isActivated), IsButton(isButton)
        {
            sf::Vector2u size = asset::AssetLoader::GetTexture(key).getSize();
            rect = {0, 0, static_cast<int>(size.x), static_cast<int>(size.y)};
            hovered = false;
        }

        /**
         * @brief Construct a new Drawable object
         *
         * @param texture the texture key
         * @param rect the rect to use from the texture
         */
        Drawable(const std::string &key, sf::IntRect rect, bool isActivated = true, bool isButton = false, float rotation = 0.0)
            : rect(rect), textureKey(key), rotation(rotation), activated(isActivated), IsButton(isButton)
        {
            hovered = false;
        }

        inline sf::Texture &getTexture() { return asset::AssetLoader::GetTexture(textureKey); }

        inline const sf::Texture &getTexture() const { return asset::AssetLoader::GetTexture(textureKey); }
        inline void switchActivated() {activated = !activated;}
        inline void switchHovered() {hovered = !hovered;}

        std::string textureKey;
        sf::IntRect rect;
        float rotation;
        bool activated;
        bool hovered;
        bool IsButton;
    };
} // namespace ecs::component
