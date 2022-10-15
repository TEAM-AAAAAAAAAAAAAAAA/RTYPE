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
        auto &position = world.registry.getComponents<component::Position>();
        auto &networkId = world.registry.getComponents<component::NetworkId>();
        auto &entityType = world.registry.getComponents<component::EntityType>();
        auto &sizes = world.registry.getComponents<component::Size>();

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
                Message msg;
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
                network::Server::getOutgoingMessages().push(network::ServerMessage(msg, std::vector<unsigned int>()));
            }
        }
    };
} // namespace ecs::systems
