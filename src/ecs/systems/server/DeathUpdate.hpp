/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** DeathUpdate
*/

#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Health.hpp"
#include "components/NetworkId.hpp"
#include "components/Dead.hpp"

namespace ecs::systems
{
    std::function<void(World &)> deathUpdate = [](World &world) {
        auto &healths = world.registry.getComponents<component::Health>();
        auto &networkId = world.registry.getComponents<component::NetworkId>();

        for (size_t i = 0; i < healths.size(); ++i) {
            auto &health = healths[i];

            if (health) {
                if (health.value().health <= 0) {
                    if (i < networkId.size()) {
                        auto &id = networkId[i];

                        if (id) {
                            std::array<char, 2> idBin = id.value().serialize();

                            network::Message msg;
                            msg[0] = ecs::constant::getPacketTypeKey(ecs::constant::PacketType::ENTITY_DEATH);
                            msg[1] = idBin[0];
                            msg[2] = idBin[1];
                            network::Server::getOutgoingMessages().push(
                                network::ServerMessage(msg, std::vector<unsigned int>()));
                        }
                    }

                    // world.registry.killEntity(world.registry.entityFromIndex(i));
                    world.registry.addComponent<component::Dead>(world.registry.entityFromIndex(i), {});
                }
            }
        }
    };
}