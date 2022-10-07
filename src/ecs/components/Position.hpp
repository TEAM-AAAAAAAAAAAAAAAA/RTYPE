/*
 * File: Position.hpp
 * Project: components
 * File Created: Monday, 3rd October 2022 3:37:48 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 7:26:30 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once
#include <cstddef>
#include <array>

namespace ecs::component
{
    struct Position {
        int x;
        int y;
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
