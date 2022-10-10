/*
** EPITECH PROJECT, by hourcadettej on 10/2/22.
** rtype
** File description:
** rtype
*/

#pragma once

#include <cstddef>

namespace ecs
{
    namespace constant
    {
        using chrono = std::chrono::high_resolution_clock;
        using chronoDuration = std::chrono::duration<double, std::milli>;

        static const std::size_t npos = -1;
        static short mapWidth = 1920;
        static short mapHeight = 1080;
    } // namespace constant
} // namespace ecs
