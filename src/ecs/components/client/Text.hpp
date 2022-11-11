/*
** EPITECH PROJECT, by hourcadettej on 10/29/22.
** rtype
** File description:
** rtype
*/

#pragma once

#include <string>
#include <utility>

namespace ecs::component
{
    struct textColor {
        short r;
        short g;
        short b;
        short a;
    };

    struct Text {

        Text(size_t marginRight = 0, const std::string &key = "nasa") : _fontKey(key), _marginRight(marginRight), _textColor({255, 255, 255, 255})
        {
            _content.emplace_back("0");
            _content.emplace_back(" / ");
            _content.emplace_back("4");
            _content.emplace_back("Rene-lick");
        };

        std::string getContent(size_t pos) const
        {
            if (pos > _content.size())
                return "";
            return _content[pos];
        };
        void setContent(size_t pos, std::string &newContent)
        {
            if (pos <= _content.size())
                _content[pos] = newContent;
        }
        inline void addContent(std::string &content) {_content.push_back(content);};
        inline void clearContent() {_content.clear();};
        inline size_t getContentSize() const {return _content.size();};
        void setTextColor(short r, short g, short b, short a)
        {
            _textColor.r = r;
            _textColor.g = g;
            _textColor.b = b;
            _textColor.a = a;
        };
        inline struct textColor getTextColor() const {return _textColor;};
        inline void setFontKey(const std::string& fontKey){_fontKey = fontKey;};
        inline const sf::Font &getFont() const { return asset::AssetLoader::GetFont(_fontKey);};
        inline void setMarginRight(size_t marginRight) {_marginRight = marginRight;};
        inline size_t getMarginRight() const {return _marginRight;};

      private:
        std::vector<std::string> _content;
        struct textColor _textColor;
        std::string _fontKey;
        size_t _marginRight;
    };
} // namespace ecs::component
