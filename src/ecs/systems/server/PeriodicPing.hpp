/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** PeriodicPing
*/

#pragma once

#include <functional>
#include <iostream>
#include "Constant.hpp"
#include "World.hpp"
#include "Server.hpp"

namespace ecs::systems
{
    /**
     * System used to send a ping to the client every so often to make sure it
     * knows the server is still up
     */
    std::function<void(World &)> periodicPing = [](World &world) {
        static auto clock = utils::constant::chrono::now();
        if (utils::constant::chronoDuration(utils::constant::chrono::now() - clock).count() > 10000) {
            network::Message msg;
            msg.fill(0);
            msg[0] = 70;
            network::Server::getOutgoingMessages().push(
                network::ServerMessage(msg, std::vector<unsigned int>()));
        }
    };
} // namespace ecs::systems
