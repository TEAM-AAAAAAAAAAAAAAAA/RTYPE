/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Position
*/

#pragma once
#include <cstddef>
#include <array>

namespace ecs::component
{
    struct Position {
        Position(int x, int y) : x(x), y(y) {}
        int x;
        int y;
        /// @brief serialize the component
        /// @return the serialized component
        std::array<char, 4> serialize()
        {
            std::array<char, 4> pos;
            size_t tmp = 0;

            tmp = x >> 8;
            pos[0] = tmp;
            pos[1] = x & 0xff;
            tmp = y >> 8;
            pos[2] = tmp;
            pos[3] = y & 0xff;
            return pos;
        }
    };
} // namespace ecs::component
