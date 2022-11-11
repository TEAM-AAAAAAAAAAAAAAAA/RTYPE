/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** playerHealthUpdate
*/

#pragma once

#include <functional>
#include <iostream>
#include "Constant.hpp"
#include "Entity.hpp"
#include "World.hpp"
#include "components/NetworkId.hpp"
#include "components/Position.hpp"

namespace ecs::systems
{
    /**
     * System used to push death of entity message to the server
     * outgoing queue when is life as gone under 0.
     */
    std::function<void(World &)> playerHealthUpdate = [](World &world) {
        auto &healths = world.registry.getComponents<component::Health>();
        auto &entity = world.registry.getComponents<component::EntityType>();
        static short lastHealth = utils::constant::maxPlayerHealth;
        for (size_t i = 0; i < healths.size(); ++i) {
            auto &health = healths[i];
            if (health && health.value().health != lastHealth) {
                if (i < entity.size()) {
                    auto &type = entity[i];
                    if (type && type.value().type == component::EntityType::Types::Player) {
                        lastHealth = health.value().health;
                        network::Message msg;
                        msg[0] = utils::constant::getPacketTypeKey(utils::constant::PacketType::HEALTH_UPDATE);
                        msg[1] = health.value().health;
                        network::Server::getOutgoingMessages().push(
                            network::ServerMessage(msg, std::vector<unsigned int>()));
                    }
                }
            }
        }
    };
} // namespace ecs::systems
