/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** ExecuteOnce
*/

#pragma once

#include <functional>
#include "../client/NetworkClient.hpp"
#include "World.hpp"

namespace ecs::systems
{
    /**
     * Login to the server only once
     */
    std::function<void(World &)> executeOnce = [](World &world) {
        static bool executed = false;

        if (!executed) {
            network::Message msg;
            msg.fill(0);
            network::Client::connect();
            network::Client::getOutgoingMessages().push(msg);
            executed = true;
        }
    };
} // namespace ecs::systems
