/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleIncomingMessage
*/

#pragma once

#include <functional>
#include <iostream>
#include "../server/Server.hpp"
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
    static void createPlayer(World &world, network::ClientMessage &msg)
    {
        ecs::Entity newPlayer = world.registry.spawn_entity();

        world.registry.addComponent<ecs::component::Position>(newPlayer, {10, 10});
        world.registry.addComponent<ecs::component::Velocity>(newPlayer, {5, 5});
        world.registry.addComponent<ecs::component::Size>(newPlayer, {32, 64});
        world.registry.addComponent<ecs::component::Direction>(newPlayer, {0, 0});
        world.registry.addComponent<ecs::component::EntityType>(newPlayer, {ecs::component::EntityType::Types::Player});
        world.registry.addComponent<ecs::component::Weapon>(newPlayer, {100, 10, 10});
        world.registry.addComponent<ecs::component::Health>(newPlayer, {100});
        world.registry.addComponent<ecs::component::NetworkId>(newPlayer, {static_cast<size_t>(newPlayer)});
        world.registry.addComponent<ecs::component::Faction>(newPlayer, {ecs::component::Faction::Factions::Players});

        std::cerr << "New connection !" << std::endl; // Debug print
        network::ServerMessage message;
        message.first.fill(0);
        message.first[1] = static_cast<size_t>(newPlayer) >> 8;
        message.first[2] = static_cast<size_t>(newPlayer) & 0xFF;
        message.second.clear();
        message.second.push_back(msg.second);
        network::Server::getOutgoingMessages().push(message);
    }

    static void movePlayer(World &world, network::ClientMessage &msg)
    {
        auto &directions = world.registry.getComponents<component::Direction>();

        for (size_t i = 0; i < directions.size(); ++i) {
            auto &dir = directions[i];

            if (dir) {
                std::cout << (int)msg.first[1] << " " << (int)msg.first[2] << std::endl;
                std::cout << dir.value().x << " " << dir.value().y << std::endl;
                dir.value().x = (int)msg.first[1];
                dir.value().y = (int)msg.first[2];
            }
        };
    }

    static std::unordered_map<char, std::function<void(World &, network::ClientMessage &msg)>> packetTypeFunction = {
        {0, createPlayer}, {ecs::Event::EventType::Move, movePlayer}};

    std::function<void(World &)> HandleIncomingMessages = [](World &world) {
        while (!network::Server::getIncomingMessages().empty()) {
            // std::cerr << "Handling messages !" << std::endl; // Debug print
            network::ClientMessage msg = network::Server::getIncomingMessages().pop();
            packetTypeFunction[msg.first[0]](world, msg);
        }
    };
} // namespace ecs::systems
