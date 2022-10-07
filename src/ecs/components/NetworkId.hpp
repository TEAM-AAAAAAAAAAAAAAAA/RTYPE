/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#pragma once
#include <cstddef>
#include <array>

namespace ecs::component
{
    struct NetworkId {
        size_t id;
        std::array<char, 2> serialize()
        {
            std::array<char, 2> arr;
            size_t tmp = 0;

            tmp = id >> 8;
            arr[0] = tmp;
            arr[1] = id & 0xff;
            return arr;
        }
    };
} // namespace ecs::component
