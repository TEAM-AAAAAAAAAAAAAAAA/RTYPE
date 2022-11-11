/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Health
*/

#pragma once

#include "Constant.hpp"

namespace ecs::component
{
    struct Health {
        int health;
        int lastHealth = utils::constant::maxPlayerHealth;
    };
} // namespace ecs::component
