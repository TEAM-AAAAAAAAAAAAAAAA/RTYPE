/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Faction
*/

#pragma once

namespace ecs::component
{
    struct Faction {
        enum Factions {
            None,
            Chefs,
            Uranus,
            Janitor,
            Alien,
        };

        Faction(Factions faction = Factions::None) : faction(faction) {}

        Factions faction;
    };
} // namespace ecs::component
