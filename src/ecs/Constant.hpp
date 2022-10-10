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
    static const std::size_t npos = -1;
    using chrono = std::chrono::high_resolution_clock;
    using chronoDuration = std::chrono::duration<double, std::milli>;
} // namespace ecs
