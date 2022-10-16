/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleIncomingMessages
*/

#pragma once

#include <functional>
#include <iostream>
#include "../client/NetworkClient.hpp"
#include "AssetManager.hpp"
#include "Constant.hpp"
#include "World.hpp"
#include "components/Direction.hpp"
#include "components/client/Controllable.hpp"

namespace ecs::systems
{
    std::function<void(World &)> SendDirection = [](World &world) {
        auto const &controllables = world.registry.getComponents<component::Controllable>();
        auto const &directions = world.registry.getComponents<component::Direction>();

        static auto clock = ecs::constant::chrono::now();
        if (ecs::constant::chronoDuration(ecs::constant::chrono::now() - clock).count() > 10) {
            clock = ecs::constant::chrono::now();
            for (size_t i = 0; i < controllables.size() && i < directions.size(); i++) {
                if (!controllables[i] || !directions[i])
                    continue;

                std::cout << "player found" << std::endl;
                network::Message msg;
                msg.fill(0);
                msg[0] = ecs::Event::EventType::Move;
                msg[1] = directions[i].value().x;
                msg[2] = directions[i].value().y;
                network::Client::getOutgoingMessages().push(msg);

                // while (world.getEvent() != ecs::Event::EventType::Null) {
                //     network::Message msg;
                //     msg.fill(0);
                //     msg[0] = world.getEvent().serialize();
                //     network::Client::getOutgoingMessages().push(msg);
                //     world.popEvent();
                // }
            }
        }
    };
}
