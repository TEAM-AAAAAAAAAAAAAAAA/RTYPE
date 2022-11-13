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
#include "components/Direction.hpp"
#include "components/EntityType.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/NetworkId.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/Weapon.hpp"

namespace ecs::systems
{
    /**
     * System used to push updated position of entity
     * to the server outgoing queue.
     */
    std::function<void(World &)> PositionUpdate = [](World &world) {
        auto &position = world.registry.getComponents<component::Position>();
        auto &networkId = world.registry.getComponents<component::NetworkId>();
        auto &entityType = world.registry.getComponents<component::EntityType>();
        auto &sizes = world.registry.getComponents<component::Size>();
        auto &velocities = world.registry.getComponents<component::Velocity>();
        auto &directions = world.registry.getComponents<component::Direction>();
        static const int packetType = 0;
        static const int firstByteId = 1;
        static const int secondByteId = 2;
        static const int valueType = 3;
        static const int firstBytePos = 4;
        static const int secondBytePos = 5;
        static const int thirdBytePos = 6;
        static const int fourthBytePos = 7;
        static const int firstByteSize = 8;
        static const int secondByteSize = 9;
        static const int thirdByteSize = 10;
        static const int fourthByteSize = 11;
        static const int firstByteVelocity = 12;
        static const int secondByteVelocity = 13;
        static const int dirX = 14;
        static const int dirY = 15;

        static auto clock = utils::constant::chrono::steady_clock::now();
        if (utils::constant::chronoDuration(utils::constant::chrono::steady_clock::now() - clock).count() > 10) {
            clock = utils::constant::chrono::steady_clock::now();
            for (size_t i = 0; i < position.size() && i < networkId.size() && i < sizes.size() && i < entityType.size()
                 && i < velocities.size() && i < directions.size();
                 i++) {
                auto &pos = position[i];
                auto &size = sizes[i];
                auto &id = networkId[i];
                auto &type = entityType[i];
                auto &vel = velocities[i];
                auto &dir = directions[i];
                if (pos && id && size && type && vel && dir) {
                    std::array<char, 2> idBin = id.value().serialize();
                    std::array<char, 4> posBin = pos.value().serialize();
                    std::array<char, 4> sizeBin = size.value().serialize();
                    network::Message msg;
                    msg[firstByteId] = idBin[0];
                    msg[secondByteId] = idBin[1];
                    msg[valueType] = type.value().type;
                    msg[firstBytePos] = posBin[0];
                    msg[secondBytePos] = posBin[1];
                    msg[thirdBytePos] = posBin[2];
                    msg[fourthBytePos] = posBin[3];
                    msg[firstByteSize] = sizeBin[0];
                    msg[secondByteSize] = sizeBin[1];
                    msg[thirdByteSize] = sizeBin[2];
                    msg[fourthByteSize] = sizeBin[3];
                    msg[firstByteVelocity] = velocities[i].value().x;
                    msg[secondByteVelocity] = velocities[i].value().y;
                    msg[dirX] = directions[i].value().x;
                    msg[dirY] = directions[i].value().y;
                    msg[packetType] = utils::constant::getPacketTypeKey(utils::constant::PacketType::ENTITY_MOVE);
                    network::Server::getOutgoingMessages().push(
                        network::ServerMessage(msg, std::vector<unsigned int>()));
                }
            }
        }
    };
} // namespace ecs::systems
