/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#pragma once
#include "../../server/Server.hpp"

namespace ecs::component
{
    /// @brief Network component needed to send messages
    struct Network {
        Network(unsigned short localPort = 8000) : serv(localPort) {};
        network::Server serv;
    };
} // namespace ecs::component
