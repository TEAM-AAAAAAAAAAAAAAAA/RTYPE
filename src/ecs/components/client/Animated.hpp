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
     * @param width the width of the sprite
     * @param origin_x the origin x position of the sprite on the sprite sheet
     * @param origin_y the origin y position of the sprite on the sprite sheet
     * @param freq the amount of frame before changing the sprite
     * @param max the max x on the sprite sheet
     * @param current the current frame of the animation
     * @param cur_freq the amount of frames since last change
     */
    struct Animated {
        int width;
        int origin_x;
        int origin_y;
        int current;
        int max;
        int freq;
        int cur_freq;
    };
} // namespace ecs::component
