/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** KeepAlive
*/

#pragma once

#include <functional>
#include <iostream>
#include "Constant.hpp"
#include "../../../client/NetworkClient.hpp"
#include "World.hpp"

namespace ecs::systems
{
    /**
     * System used to send a ping to the server every so often to make sure it
     * knows the client is still up
     */
    std::function<void(World &)> keepAlive = [](World &world) {
        if (utils::constant::chronoDuration(utils::constant::chrono::now() - network::Client::getLastPing()).count() > 5000) {
            network::Message msg;
            msg.fill(0);
            msg[0] = 70;
            network::Client::getOutgoingMessages().push(msg);
        }
    };
} // namespace ecs::systems
