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

namespace ecs::systems
{
    /**
     * System used to push updated position of entity to the server outgoing queue.
     */
    std::function<void(World &)> serverPush = [](World &world) {
        auto &network = world.registry.getComponents<component::Network>();
        auto &position = world.registry.getComponents<component::Position>();
        auto &networkId = world.registry.getComponents<component::NetworkId>();
        auto &serv = network[0];

        for (size_t i = 0; i < network.size() && !serv; i++)
            serv = network[i];
        if (!serv) {
            std::cerr << "Error: Server component not found" << std::endl;
            return;
        }
        for (size_t i = 0; i < position.size() && i < networkId.size(); i ++) {
            auto &pos = position[i];
            auto &id = networkId[i];
            if (pos && id) {
                std::array<char, 2> idBin = id.serialize();
                std::array<char, 4> posBin = pos.serialize();
                std::array<char, 7> msg;
                msg[0] = idBin[0];
                msg[1] = idBin[1];
                msg[2] = posBin[0];
                msg[3] = posBin[1];
                msg[4] = posBin[2];
                msg[5] = posBin[3];
                msg[6] = 8;
                serv.push(msg); // This is to be replaced when possible, it will not work nor should it
            }
        }
    };
} // namespace ecs::systems
