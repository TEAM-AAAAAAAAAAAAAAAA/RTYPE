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
            Laser,
            Rocket,
            UranusBattleCruiser,
            UranusDreadNought,
            UranusFighter,
            UranusFrigate,
            UranusScout,
            UranusTorpedo,
            JanitorBattleCruiser,
            JanitorDreadNought,
            JanitorFighter,
            JanitorFrigate,
            JanitorScout,
            JanitorTorpedo,
            AlienBattleCruiser,
            AlienDreadNought,
            AlienFighter,
            AlienFrigate,
            AlienScout,
            AlienTorpedo,
            NoodleMonster,
        };
        EntityType(char type) : type(type) {}
        char type;
    };
} // namespace ecs::component
