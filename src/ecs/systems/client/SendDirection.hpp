/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleIncomingMessages
*/

#pragma once

#include <functional>
#include <iostream>
#include "../client/NetworkClient.hpp"
#include "Constant.hpp"
#include "World.hpp"
#include "components/Direction.hpp"
#include "components/client/Controllable.hpp"

namespace ecs::systems
{
    /**
     * Send direction system used to fill the array of messages to the server regarding the direction of the player
     */
    std::function<void(World &)> SendDirection = [](World &world) {
        auto const &controllables = world.registry.getComponents<component::Controllable>();
        auto &directions = world.registry.getComponents<component::Direction>();

        static auto clock = utils::constant::chrono::now();
        if (utils::constant::chronoDuration(utils::constant::chrono::now() - clock).count() > 10) {
            clock = utils::constant::chrono::now();
            for (size_t i = 0; i < controllables.size() && i < directions.size(); i++) {
                if (!controllables[i] || !directions[i])
                    continue;

                if (directions[i].value().hasMoved) {
                    network::Message msg;
                    msg.fill(0);
                    msg[0] = utils::constant::getPacketTypeKey(utils::constant::PLAYER_MOVE);
                    msg[1] = directions[i].value().x;
                    msg[2] = directions[i].value().y;
                    network::Client::getOutgoingMessages().push(msg);
                    directions[i].value().hasMoved = false;
                }
            }
        }
    };
} // namespace ecs::systems
