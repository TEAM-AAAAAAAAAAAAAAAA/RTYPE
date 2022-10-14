/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** PositionUpdate
*/

#pragma once

#include <functional>
#include <iostream>
#include "EntityType.hpp"
#include "Network.hpp"
#include "NetworkId.hpp"
#include "Position.hpp"
#include "Size.hpp"
#include "World.hpp"

namespace ecs::systems
{
    /**
     * System used to push updated position of entity
     * to the server outgoing queue.
     */
    std::function<void(World &)> positionUpdate = [](World &world) {
        auto &network = world.registry.getComponents<component::Network>();
        auto &position = world.registry.getComponents<component::Position>();
        auto &networkId = world.registry.getComponents<component::NetworkId>();
        auto &entityType = world.registry.getComponents<component::EntityType>();
        auto &sizes = world.registry.getComponents<component::Size>();

        if (network.size() == 0) {
            std::cerr << "Error: Network component not found" << std::endl;
            return;
        }
        size_t netId = 0;
        for (netId; netId < network.size(); netId++) {
            if (network[netId])
                break;
        }
        if (netId == network.size()) {
            std::cerr << "Error: Network component not found" << std::endl;
            return;
        }
        auto &serv = network[netId];
        if (!serv) {
            std::cerr << "Error: Network component not found" << std::endl;
            return;
        }

        for (size_t i = 0; i < position.size() && i < networkId.size() && i < sizes.size() && i < entityType.size();
             i++) {
            auto &pos = position[i];
            auto &size = sizes[i];
            auto &id = networkId[i];
            auto &type = entityType[i];
            if (pos && id) {
                std::array<char, 2> idBin = id.value().serialize();
                std::array<char, 4> posBin = pos.value().serialize();
                std::array<char, 2> sizeBin = size.value().serialize();
                std::array<char, 10> msg;
                msg[0] = idBin[0];
                msg[1] = idBin[1];
                msg[2] = type.value().type;
                msg[3] = posBin[0];
                msg[4] = posBin[1];
                msg[5] = posBin[2];
                msg[6] = posBin[3];
                msg[7] = sizeBin[0];
                msg[8] = sizeBin[1];
                msg[9] = ecs::constant::getPacketTypeKey(ecs::constant::PacketType::ENTITY_MOVE);
                serv.value().serv.outgoingQueue.push(network::ServerMessage(msg, std::vector<unsigned int>()));
            }
        }
    };
} // namespace ecs::systems
