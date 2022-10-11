/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** PositionUpdate
*/

#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "Network.hpp"
#include "Position.hpp"
#include "NetworkId.hpp"
#include "Size.hpp"
#include "EntityType.hpp"

namespace ecs::systems
{
    /**
     * System used to push updated position of entity
     * to the server outgoing queue.
     */
    std::function<void(World &)> serverPush = [](World &world) {
        auto &network = world.registry.getComponents<component::Network>();
        auto &position = world.registry.getComponents<component::Position>();
        auto &networkId = world.registry.getComponents<component::NetworkId>();
        auto &entityType = world.registry.getComponents<component::EntityType>();
        auto &size = world.registry.getComponents<component::Size>();
        auto &serv = network[0];

        for (size_t i = 0; i < network.size() && !serv; i++)
            serv = network[i];
        if (!serv) {
            std::cerr << "Error: Server component not found" << std::endl;
            return;
        }
        for (size_t i = 0; i < position.size() && i < networkId.size() && i < size.size(); i ++) {
            auto &pos = position[i];
            auto &size = size[i];
            auto &id = networkId[i];
            auto &type = entityType[i];
            if (pos && id) {
                std::array<char, 2> idBin = id.serialize();
                std::array<char, 4> posBin = pos.serialize();
                std::array<char, 2> sizeBin = size.serialize();
                std::array<char, 8> msg;
                msg[0] = idBin[0];
                msg[1] = idBin[1];
                msg[2] = type.type;
                msg[3] = posBin[0];
                msg[4] = posBin[1];
                msg[5] = posBin[2];
                msg[6] = posBin[3];
                msg[7] = sizeBin[0];
                msg[8] = sizeBin[1];
                msg[9] = ecs::getPacketTypeKey(ecs::ENTITY_MOVE);;
                serv.serv.outgoingQueue.push(Network::ServerMessage(msg, std::vector<unsigned int>()));
            }
        }
    };
} // namespace ecs::systems
