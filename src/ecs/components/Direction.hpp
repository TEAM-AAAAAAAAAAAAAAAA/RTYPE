/*
 * File: Direction.hpp
 * Project: components
 * File Created: Tuesday, 4th October 2022 7:10:05 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 7:22:19 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
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
        int x;
        int y;
    };
} // namespace ecs::component
