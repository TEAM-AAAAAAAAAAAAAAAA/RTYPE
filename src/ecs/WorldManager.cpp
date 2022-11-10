/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** WorldManager
*/

#include "WorldManager.hpp"

namespace ecs
{
    WorldManager &WorldManager::getInstance()
    {
        static WorldManager _Instance;
        return _Instance;
    }
}
