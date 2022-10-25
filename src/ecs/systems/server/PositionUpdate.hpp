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

        static auto clock = ecs::constant::chrono::now();
        if (ecs::constant::chronoDuration(ecs::constant::chrono::now() - clock).count() > 100) {
            clock = ecs::constant::chrono::now();
            for (size_t i = 0; i < position.size() && i < networkId.size() && i < sizes.size() && i < entityType.size()
                 && i < velocities.size();
                 i++) {
                auto &pos = position[i];
                auto &size = sizes[i];
                auto &id = networkId[i];
                auto &type = entityType[i];
                auto &direction = directions[i];
                if (pos && id && size && type && direction) {
                    std::array<char, 2> idBin = id.value().serialize();
                    std::array<char, 4> posBin = pos.value().serialize();
                    std::array<char, 2> sizeBin = size.value().serialize();
                    network::Message msg;
                    msg[1] = idBin[0];
                    msg[2] = idBin[1];
                    msg[3] = type.value().type;
                    msg[4] = posBin[0];
                    msg[5] = posBin[1];
                    msg[6] = posBin[2];
                    msg[7] = posBin[3];
                    msg[8] = sizeBin[0];
                    msg[9] = sizeBin[1];
                    msg[10] = velocities[i].value().x;
                    msg[11] = velocities[i].value().y;
                    msg[12] = direction.value().serialize();
                    msg[0] = ecs::constant::getPacketTypeKey(ecs::constant::PacketType::ENTITY_MOVE);
                    network::Server::getOutgoingMessages().push(
                        network::ServerMessage(msg, std::vector<unsigned int>()));
                }
            }
        }
    };
} // namespace ecs::systems
