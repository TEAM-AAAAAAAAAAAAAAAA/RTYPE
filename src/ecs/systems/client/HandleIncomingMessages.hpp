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
#include "World.hpp"
#include "components/EntityType.hpp"
#include "components/NetworkId.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/client/Controllable.hpp"
#include "components/client/Drawable.hpp"
#include "components/client/Shootable.hpp"

namespace ecs::systems
{
    static size_t selfId = 0;
    static void movePacketHandle(World &world, network::Message &msg)
    {
        auto &positions = world.registry.getComponents<component::Position>();
        auto &networkId = world.registry.getComponents<component::NetworkId>();
        auto &velocities = world.registry.getComponents<component::Velocity>();
        auto &sizes = world.registry.getComponents<component::Size>();
        auto &types = world.registry.getComponents<component::EntityType>();
        auto &directions = world.registry.getComponents<component::Direction>();
        size_t msgId = (unsigned char)msg[1] << 8U | (unsigned char)msg[2];
        size_t posX = (unsigned char)msg[4] << 8U | (unsigned char)msg[5];
        size_t posY = (unsigned char)msg[6] << 8U | (unsigned char)msg[7];

        for (size_t i = 0; i < networkId.size(); i++)
            if (networkId[i] && networkId[i]->id == msgId) {
                if (i < sizes.size() && sizes[i]) {
                    sizes[i].value().width = msg[8];
                    sizes[i].value().height = msg[9];
                }
                if (i < positions.size() && positions[i]) {
                    positions[i].value().x = posX;
                    positions[i].value().y = posY;
                }
                if (i < types.size() && types[i]) {
                    types[i].value().type = msg[3];
                }
                if (i < velocities.size() && velocities[i]) {
                    velocities[i].value().x = msg[10];
                    velocities[i].value().y = msg[11];
                }
                if (i < directions.size() && directions[i]) {
                    component::Direction d = component::Direction::deserialize(msg[12]);
                    directions[i].value().x = d.x;
                    directions[i].value().y = d.y;
                }
                return;
            }
        Entity newEntity = world.registry.spawn_entity();
        if (msg[3] == component::EntityType::Types::Player && msgId != selfId)
            world.registry.addComponent<component::EntityType>(newEntity, {component::EntityType::Types::OtherPlayer});
        else
            world.registry.addComponent<component::EntityType>(newEntity, {msg[3]});
        world.registry.addComponent<component::NetworkId>(newEntity, {msgId});
        world.registry.addComponent<component::Position>(newEntity, {(int)posX, (int)posY});
        world.registry.addComponent<component::Size>(newEntity, {msg[8], msg[9]});
        if (msg[3] == component::EntityType::Types::Player) {
            world.registry.addComponent<component::Direction>(newEntity, {0, 0});
            world.registry.addComponent<component::Velocity>(newEntity, {msg[10], msg[11]});
            if (selfId != msgId) {
                world.registry.addComponent<component::Drawable>(newEntity,
                    {ecs::crossPlatformPath("src", "demo", "assets", "textures", "players.gif"), {1, 1, 32, 16}});
            } else {
                world.registry.addComponent<component::Drawable>(newEntity,
                    {ecs::crossPlatformPath("src", "demo", "assets", "textures", "players.gif"), {1, 1, 32, 16}});
                world.registry.addComponent<ecs::component::Shootable>(
                    newEntity, ecs::component::Shootable(sf::Keyboard::Space));
                world.registry.addComponent<ecs::component::Controllable>(
                    newEntity, {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D});
            }
        } else if (msg[3] == component::EntityType::Types::EnemyBase) {
            world.registry.addComponent<component::Drawable>(newEntity,
                {ecs::crossPlatformPath("src", "demo", "assets", "textures", "players.gif"), {1, 18, 32, 16}});
        } else if (msg[3] == component::EntityType::Types::Bullet) {
            component::Direction d = component::Direction::deserialize(msg[12]);
            world.registry.addComponent<component::Direction>(newEntity, {d.x, d.y});
            world.registry.addComponent<component::Drawable>(
                newEntity, {ecs::crossPlatformPath("src", "demo", "assets", "textures", "players.gif"), {5, 5, 1, 1}});
        }
    }

    static void firstMessageHandle(World &world, network::Message &msg)
    {
        selfId = (unsigned char)msg[1] << 8U | (unsigned char)msg[2];
    }

    static std::unordered_map<char, std::function<void(World &, network::Message &msg)>> packetTypeFunction = {
        {8, movePacketHandle}, {0, firstMessageHandle}};

    std::function<void(World &)> HandleIncomingMessages = [](World &world) {
        while (!network::Client::getIncomingMessages().empty()) {
            network::Message msg = network::Client::getIncomingMessages().pop();
            packetTypeFunction[msg[0]](world, msg);
        }
    };
} // namespace ecs::systems
