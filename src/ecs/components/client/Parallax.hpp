/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Parallax
*/

#pragma once

namespace ecs::component
{
    /**
     * Parallax component allows us to more easily manipulate the parallaxed background
     */
    struct Parallax {
        int threshold;
        int position;
    };
} // namespace ecs::component
