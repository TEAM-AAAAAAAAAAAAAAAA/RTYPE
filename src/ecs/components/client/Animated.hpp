/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Animated
*/

#pragma once

namespace ecs::component
{
    /**
     * Animated component allows draw system function to render the animation for the sprite
     */
    struct Animated {
        int width;
        int origin_x;
        int origin_y;
        int current;
        int freq;
        int cur_freq;
    };
} // namespace ecs::component
