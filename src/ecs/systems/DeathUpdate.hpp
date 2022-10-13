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
#include "EntityLife.hpp"
#include "Network.hpp"
#include "NetworkId.hpp"
#include "Position.hpp"
#include "World.hpp"

namespace ecs::systems
{
    /**
     * System used to push death of entity message to the server
     * outgoing queue when is life as gone under 0.
     */
    std::function<void(World &)> serverPush = [](World &world) {
        auto &network = world.registry.getComponents<component::Network>();
        auto &position = world.registry.getComponents<component::Position>();
        auto &life = world.registry.getComponents<component::EntityLife>();
        auto &networkId = world.registry.getComponents<component::NetworkId>();
        auto &serv = network[0];

        for (size_t i = 0; i < network.size() && !serv; i++)
            serv = network[i];
        if (!serv) {
            std::cerr << "Error: Server component not found" << std::endl;
            return;
        }
        for (size_t i = 0; i < position.size() && i < networkId.size(); i++) {
            auto &pos = position[i];
            auto &id = networkId[i];
            auto &li = life[i];
            if (li.value().life <= 0 && pos && id) {
                std::array<char, 2> idBin = id.value().serialize();
                std::array<char, 4> posBin = pos.value().serialize();
                std::array<char, 7> msg;
                msg[0] = idBin[0];
                msg[1] = idBin[1];
                msg[2] = posBin[0];
                msg[3] = posBin[1];
                msg[4] = posBin[2];
                msg[5] = posBin[3];
                msg[6] = ecs::getPacketTypeKey(ecs::ENTITY_DEATH);
                serv.value().serv.outgoingQueue.push(
                    msg); // This is to be replaced when possible, it will not work nor should it
            }
        }
    };
} // namespace ecs::systems
