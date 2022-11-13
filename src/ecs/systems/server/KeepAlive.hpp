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
        static auto clock = utils::constant::chrono::steady_clock::now();
        std::map<uint32_t, std::chrono::steady_clock::time_point> _clientLastPing =
            network::Server::getClientLastPings();
        if (utils::constant::chronoDuration(utils::constant::chrono::steady_clock::now() - clock).count() > 1000) {
            clock = utils::constant::chrono::steady_clock::now();
            for (auto &ping : _clientLastPing) {
                auto lastPing = ping.second;
                if (utils::constant::chronoDuration(utils::constant::chrono::steady_clock::now() - lastPing).count() > 5000) {
                    network::Message msg;
                    msg.fill(0);
                    msg[0] = utils::constant::getPacketTypeKey(utils::constant::KEEP_ALIVE);
                    network::Server::getOutgoingMessages().push(
                        network::ServerMessage(msg, std::vector<unsigned int>()));
                }
            }
        }
    };
} // namespace ecs::systems
