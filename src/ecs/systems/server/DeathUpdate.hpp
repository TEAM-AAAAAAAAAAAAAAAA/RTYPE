/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** PositionUpdate
*/

#pragma once

#include <functional>
#include <iostream>
#include "Constant.hpp"
#include "World.hpp"
#include "components/NetworkId.hpp"
#include "components/Position.hpp"
#include "components/server/FollowEntity.hpp"

namespace ecs::systems
{
    /**
     * System used to push death of entity message to the server
     * outgoing queue when is life as gone under 0.
     */
    std::function<void(World &)> deathUpdate = [](World &world) {
        auto &healths = world.registry.getComponents<component::Health>();
        auto &networkId = world.registry.getComponents<component::NetworkId>();
        std::map<unsigned int, size_t> _clientToEntID = network::Server::getClientToEntID();
        static auto clock = utils::constant::chrono::now();
        auto const &follow = world.registry.getComponents<component::FollowEntity>();

        for (size_t i = 0; i < healths.size(); i++) {
            auto &health = healths[i];

            if (health) {
                if (health.value().health <= 0) {
                    if (i < networkId.size()) {
                        auto &id = networkId[i];

                        if (id) {
                            std::array<char, 2> idBin = id.value().serialize();

                            network::Message msg;
                            msg[0] = utils::constant::getPacketTypeKey(utils::constant::PacketType::ENTITY_DEATH);
                            msg[1] = idBin[0];
                            msg[2] = idBin[1];
                            network::Server::getOutgoingMessages().push(
                                network::ServerMessage(msg, std::vector<unsigned int>()));
                        }
                    }
                    for (std::size_t j = 0; j < follow.size(); j++) {
                        if (follow[j]) {
                            if (follow[j].value().entityId == i) {
                                if (j < networkId.size()) {
                                    auto &id = networkId[j];

                                    if (id) {
                                        std::array<char, 2> idBin = id.value().serialize();

                                        network::Message msg;
                                        msg[0] = utils::constant::getPacketTypeKey(
                                            utils::constant::PacketType::ENTITY_DEATH);
                                        msg[1] = idBin[0];
                                        msg[2] = idBin[1];
                                        network::Server::getOutgoingMessages().push(
                                            network::ServerMessage(msg, std::vector<unsigned int>()));
                                    }
                                }
                                world.registry.killEntity(world.registry.entityFromIndex(j));
                            }
                        }
                    }
                    world.registry.killEntity(world.registry.entityFromIndex(i));
                }
            }
        }
        if (utils::constant::chronoDuration(utils::constant::chrono::now() - clock).count() > 100) {
            clock = utils::constant::chrono::now();
            for (size_t i = 0; i < networkId.size(); ++i) {
                auto &id = networkId[i];
                int clientId = 0;

                if (id) {
                    for (auto &[key, value] : _clientToEntID)
                        if (value == id.value().id) {
                            clientId = key;
                        }
                    if (utils::constant::chronoDuration(
                            utils::constant::chrono::now() - network::Server::getLastPing(clientId))
                            .count()
                        > 10000) {
                        std::array<char, 2> idBin = id.value().serialize();

                        network::Message msg;
                        msg[0] = utils::constant::getPacketTypeKey(utils::constant::PacketType::ENTITY_DEATH);
                        msg[1] = idBin[0];
                        msg[2] = idBin[1];
                        network::Server::getOutgoingMessages().push(
                            network::ServerMessage(msg, std::vector<unsigned int>()));
                        network::Server::removeClient(clientId);
                        world.registry.killEntity(world.registry.entityFromIndex(i));
                    }
                }
            }
        }
    };
} // namespace ecs::systems
