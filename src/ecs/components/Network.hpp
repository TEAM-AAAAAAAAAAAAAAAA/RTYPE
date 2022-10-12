/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#pragma once
#include "Server.hpp"

namespace ecs::component
{
    /// @brief Network component needed to send messages
    struct Network {
        Network::Server serv;
    };
} // namespace ecs::component
