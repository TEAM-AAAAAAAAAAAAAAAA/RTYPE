/*
** EPITECH PROJECT, by hourcadettej on 10/29/22.
** rtype
** File description:
** rtype
*/

#pragma once

#include <string>
#include <utility>
#include "SFML/Graphics/Text.hpp"

namespace ecs::component
{
    struct Text {
        explicit Text(const std::string &cont, const std::string &key, sf::Color col = sf::Color::White)
            : content(cont), fontKey(key), color(col), value(std::string()){};

        inline sf::Font &getFont() { return asset::AssetLoader::GetFont(fontKey); }

        inline const sf::Font &getFont() const { return asset::AssetLoader::GetFont(fontKey); }

        inline void setValue(const std::string &val) { value = val; }

        std::string content;
        std::string value;
        std::string fontKey;
        sf::Color color;
    };
} // namespace ecs::component
