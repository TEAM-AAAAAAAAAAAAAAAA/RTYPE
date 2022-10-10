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
        Projectile(int damage) : Damage(damage) {}

        int Damage;
    };
} // namespace ecs::component
