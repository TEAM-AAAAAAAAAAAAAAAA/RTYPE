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
     * hasMoved is used to know if the entity changed its direction since the last synchronisation with the server
     */
    struct Direction {
        Direction(char x, char y, bool hasMoved = false) : x(x), y(y), hasMoved(hasMoved) {}
        char x;
        char y;
        bool hasMoved;
    };
} // namespace ecs::component
