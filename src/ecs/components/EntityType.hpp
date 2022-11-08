/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** EntityType
*/

#pragma once

namespace ecs::component
{
    /// @brief EntityType component
    struct EntityType {
        enum Types {
            Player,
            OtherPlayer,
            Bullet,
            EnergySphere,
            EnemyBase,
            EnemyBoss,
        };
        EntityType(char type) : type(type) {}
        char type;
    };
} // namespace ecs::component
