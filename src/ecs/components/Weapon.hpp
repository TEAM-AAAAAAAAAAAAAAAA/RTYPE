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
        Weapon(int shootDelay, int damage, int projSpeed, bool hasSuper = false, int superDamage = 0, int superLoadingTime = 0)
            : shootDelay(shootDelay * 1000000), damage(damage), projSpeed(projSpeed), hasSuper(hasSuper), superDamage(superDamage), superLoadingTime(superLoadingTime), lastShoot(0)
        {
        }

        int shootDelay;
        int damage;
        int projSpeed;
        int64_t lastShoot;
        bool hasSuper;
        int superDamage;
        int superLoadingTime;
    };
} // namespace ecs::component
