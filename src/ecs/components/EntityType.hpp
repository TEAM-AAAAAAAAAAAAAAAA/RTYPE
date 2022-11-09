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
            UranusBattlecruiser,
            UranusDreadnought,
            UranusFighter,
            UranusFrigate,
            UranusScout,
            UranusTorpedo,
            JanitorBattlecruiser,
            JanitorDreadnought,
            JanitorFighter,
            JanitorFrigate,
            JanitorScout,
            JanitorTorpedo,
            AlienBattlecruiser,
            AlienDreadnought,
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
