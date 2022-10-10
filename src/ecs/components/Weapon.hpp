/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Weapon
*/

#pragma once

#include <chrono>

namespace ecs::component
{
    struct Weapon {
        Weapon(int shootDelay, int damage, bool hasSuper = false, int superDamage = 0, int superLoadingTime = 0)
            : ShootDelay(shootDelay * 1000000), Damage(damage), HasSuper(hasSuper), SuperDamage(superDamage), SuperLoadingTime(superLoadingTime), LastShoot(0)
        {
        }

        int ShootDelay;
        int Damage;
        int64_t LastShoot;
        bool HasSuper;
        int SuperDamage;
        int SuperLoadingTime;
    };
} // namespace ecs::component
