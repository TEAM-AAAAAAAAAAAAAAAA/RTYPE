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

        char serialize()
        {
            char dir;

            if (x == -1 && y == -1)
                return 0 & 0xff;
            else if (x == -1 && y == 0)
                return 1 & 0xff;
            else if (x == 0 && y == -1)
                return 2 & 0xff;
            else if (x == 0 && y == 0)
                return 3 & 0xff;
            else if (x == 1 && y == 0)
                return 4 & 0xff;
            else if (x == 0 && y == 1)
                return 5 & 0xff;
            else
                return 6 & 0xff;
        }

        static Direction deserialize(char dir)
        {
            if (dir == 0 & 0xff)
                return Direction(-1, -1);
            else if (dir == 1 & 0xff)
                return Direction(-1, 0);
            else if (dir == 2 & 0xff)
                return Direction(0, -1);
            else if (dir == 3 & 0xff)
                return Direction(0, 0);
            else if (dir == 4 & 0xff)
                return Direction(1, 0);
            else if (dir == 5 & 0xff)
                return Direction(0, 1);
            else
                return Direction(1, 1);
        }
    };
} // namespace ecs::component
