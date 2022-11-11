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
            PlayerBot,
            Bullet,
            EnergySphere,
            Laser,
            Rocket,
            Asteroid,
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
        EntityType(char type) : type(static_cast<Types>(type)) {}
        EntityType(Types type) : type(type) {}
        Types type;
    };
} // namespace ecs::component
