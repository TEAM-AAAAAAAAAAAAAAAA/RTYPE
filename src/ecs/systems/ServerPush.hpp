#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "Network.hpp"

namespace ecs::systems
{
    /**
     * System used to pop incoming tasks given by clients.
     */
    std::function<void(World &)> serverPush = [](World &world) {
        auto &network = world.registry.getComponents<component::Network>();

        for (size_t i = 0; i < network.size(); i++) {
            auto &serv = network[i];
            if (serv) {
                serv.serv.outgoingQueue.push(Network::ServerMessage("Hey there", std::vector<unsigned int>()));
            }
        }
    };
} // namespace ecs::systems
