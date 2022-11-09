/*
** EPITECH PROJECT, by hourcadettej on 10/29/22.
** rtype
** File description:
** rtype
*/

#pragma once

#include <string>
#include <utility>
#include "sfml/Graphics/Text.hpp"

namespace ecs::component
{
    struct Text {
        explicit Text(std::string &content, const std::string &key, unsigned int size = 42, sf::Color color)
            : _content(content), _fontKey(key) _size(size), _color(color){};

        inline std::string getContent() const { return _content; };
        inline void setContent(std::string &content) { _content = content; };

        inline sf::Font &getFont() { return asset::AssetLoader::GetFont(_fontKey); }

        inline const sf::Font &getFont() const { return asset::AssetLoader::GetFont(_fontKey); }

      private:
        std::string _content;
        std::string _fontKey;
        unsigned int _size;
        sf::Color _color;
    };
} // namespace ecs::component
