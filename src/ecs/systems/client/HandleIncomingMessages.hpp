/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleIncomingMessages
*/

#pragma once

#include <functional>
#include <iostream>
#include <valarray>
#include "../client/NetworkClient.hpp"
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
        using AnimFrame = ecs::component::Animated::AnimFrame;

        auto &positions = world.registry.getComponents<component::Position>();
        auto &networkId = world.registry.getComponents<component::NetworkId>();
        auto &velocities = world.registry.getComponents<component::Velocity>();
        auto &sizes = world.registry.getComponents<component::Size>();
        auto &types = world.registry.getComponents<component::EntityType>();
        auto &directions = world.registry.getComponents<component::Direction>();
        size_t msgId = (unsigned char)msg[1] << 8U | (unsigned char)msg[2];
        component::EntityType type = msg[3];
        int posX = (unsigned char)msg[4] << 8U | (unsigned char)msg[5];
        int posY = (unsigned char)msg[6] << 8U | (unsigned char)msg[7];
        int sizeX = msg[8];
        int sizeY = msg[9];
        int velX = msg[10];
        int velY = msg[11];
        char dirX = msg[12];
        char dirY = msg[13];

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
                if (i < velocities.size() && velocities[i] && msg[3]) {
                    velocities[i].value().x = msg[10];
                    velocities[i].value().y = msg[11];
                }
                if (msgId != selfId && i < directions.size() && directions[i]) {
                    directions[i].value().x = dirX;
                    directions[i].value().y = dirY;
                }
                return;
            }
        Entity newEntity = world.registry.spawn_entity();
        world.registry.addComponent<component::Direction>(newEntity, {dirX, dirY});
        world.registry.addComponent<component::NetworkId>(newEntity, {msgId});
        world.registry.addComponent<component::Position>(newEntity, {posX, posY});
        world.registry.addComponent<component::Velocity>(newEntity, {velX, velY});
        world.registry.addComponent<component::EntityType>(newEntity, {type.type});
        world.registry.addComponent<component::Size>(newEntity, {sizeX, sizeY});
        switch (type.type) {
            case component::EntityType::Types::Player:
                if (msgId != selfId)
                    world.registry.addComponent<component::EntityType>(
                        newEntity, {component::EntityType::Types::OtherPlayer});
                else {
                    world.registry.addComponent<component::EntityType>(
                        newEntity, {component::EntityType::Types::Player});
                    world.registry.addComponent<ecs::component::Shootable>(
                        newEntity, ecs::component::Shootable(sf::Keyboard::Space));
                    world.registry.addComponent<ecs::component::Controllable>(
                        newEntity, {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D});
                }
                world.registry.addComponent<component::Drawable>(newEntity, {"players", {1, 1, 32, 16}});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                    {AnimFrame(1, 1, 32, 16, 100), AnimFrame(34, 1, 32, 16, 100), AnimFrame(67, 1, 32, 16, 100),
                        AnimFrame(100, 1, 32, 16, 100), AnimFrame(133, 1, 32, 16, 100), AnimFrame(100, 1, 32, 16, 100),
                        AnimFrame(67, 1, 32, 16, 100), AnimFrame(34, 1, 32, 16, 100)});
                break;
            case component::EntityType::Types::EnemyBase:
                world.registry.addComponent<component::Drawable>(newEntity, {"players", {1, 18, 32, 16}});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                    {AnimFrame(1, 18, 32, 16, 100), AnimFrame(34, 18, 32, 16, 100), AnimFrame(67, 18, 32, 16, 100),
                        AnimFrame(100, 18, 32, 16, 100), AnimFrame(133, 18, 32, 16, 100),
                        AnimFrame(100, 18, 32, 16, 100), AnimFrame(67, 18, 32, 16, 100),
                        AnimFrame(34, 18, 32, 16, 100)});
                break;
            case component::EntityType::Types::Bullet:
                world.registry.addComponent<component::Drawable>(newEntity,
                    {"bullet", {10, 7, 12, 19},
                        std::atan2(static_cast<float>(dirX), static_cast<float>(dirY)) * 180 / 3.14159265359f});
                world.registry.addComponent<component::Animated>(newEntity,
                    {AnimFrame(10, 7, 12, 19, 100), AnimFrame(42, 7, 12, 19, 100), AnimFrame(74, 7, 12, 19, 100),
                        AnimFrame(106, 7, 12, 19, 100)});
                break;
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
