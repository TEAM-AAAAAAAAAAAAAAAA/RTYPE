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
    struct Text {
        explicit Text(std::string &content) : _content(content){};

        inline std::string getContent() const { return _content;};
        inline void setContent(std::string &content) {_content = content;};

      private:
        std::string _content;
    };
} // namespace ecs::component
