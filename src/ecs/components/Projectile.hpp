/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Projectile
*/

#pragma once

namespace ecs::component
{
    struct Projectile {
        Projectile(int damage) : damage(damage) {}

        int damage;
    };
} // namespace ecs::component
