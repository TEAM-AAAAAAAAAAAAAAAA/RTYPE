/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** KeepAlive
*/

#pragma once

#include <functional>
#include <iostream>
#include "../../../server/Server.hpp"
#include "Constant.hpp"
#include "World.hpp"

namespace ecs::systems
{
    /**
     * System used to send a ping to the server every so often to make sure it
     * knows the client is still up
     */
    std::function<void(World &)> keepAlive = [](World &world) {
        static auto clock = utils::constant::chrono::now();
        std::map<uint32_t, std::chrono::_V2::system_clock::time_point> _clientLastPing =
            network::Server::getClientLastPings();
        if (utils::constant::chronoDuration(utils::constant::chrono::now() - clock).count() > 1000) {
            clock = utils::constant::chrono::now();

            for (auto &ping : _clientLastPing) {
                if (utils::constant::chronoDuration(utils::constant::chrono::now() - ping.second).count() > 5000) {
                    network::Message msg;
                    msg.fill(0);
                    msg[0] = 70;
                    network::Server::getOutgoingMessages().push(
                        network::ServerMessage(msg, std::vector<unsigned int>()));
                }
            }
        }
    };
} // namespace ecs::systems
