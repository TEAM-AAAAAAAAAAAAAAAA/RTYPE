/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Direction
*/

#pragma once

namespace ecs::component
{
    /**
     * Direction component is used to know where the entity is moving
     * x represents the x-axis (horizontally)
     * y represents the y-axis (vertically)
     */
    struct Direction {
        Direction(int x, int y, bool hasMoved = 0) : x(x), y(y), hasMoved(hasMoved) {}
        int x;
        int y;
        bool hasMoved;
    };
} // namespace ecs::component
