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
     * @param threshold the position at which the background will be reset
     * @param position the original position of the background
     */
    struct Parallax {
        int threshold;
        int position;
    };
} // namespace ecs::component
