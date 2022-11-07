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
                    world.registry.addComponent<ecs::component::Controllable>(newEntity,
                        {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::H});
                    world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                }
                world.registry.addComponent<component::Drawable>(newEntity, {"players", {1, 1, 32, 16}});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                    {AnimFrame(1, 1, 32, 16, 100), AnimFrame(34, 1, 32, 16, 100), AnimFrame(67, 1, 32, 16, 100),
                        AnimFrame(100, 1, 32, 16, 100), AnimFrame(133, 1, 32, 16, 100), AnimFrame(100, 1, 32, 16, 100),
                        AnimFrame(67, 1, 32, 16, 100), AnimFrame(34, 1, 32, 16, 100)});
                break;
            case component::EntityType::Types::EnemyBase:
                world.registry.addComponent<component::Drawable>(newEntity, {"players", {1, 18, 32, 16}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
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
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                break;
            // case component::EntityType::Types::EnergySphere:
            //     world.registry.addComponent<component::Drawable>(newEntity,
            //         {"bullet", {0, 0, 32, 32},
            //             std::atan2(static_cast<float>(dirX), static_cast<float>(dirY)) * 180 / 3.14159265359f});
            //     world.registry.addComponent<component::Animated>(newEntity,
            //         {AnimFrame(0, 0, 32, 32, 100), AnimFrame(32, 0, 32, 32, 100), AnimFrame(64, 0, 32, 32, 100),
            //             AnimFrame(96, 0, 32, 32, 100), AnimFrame(128, 0, 32, 32, 100), AnimFrame(160, 0, 32, 32, 100),
            //             AnimFrame(192, 0, 32, 32, 100), AnimFrame(224, 0, 32, 32, 100), AnimFrame(256, 0, 32, 32, 100),
            //             AnimFrame(288, 0, 32, 32, 100)});
            //     world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
            //     break;
        }
    }

    static void firstMessageHandle(World &world, network::Message &msg)
    {
        selfId = (unsigned char)msg[1] << 8U | (unsigned char)msg[2];
    }

    static void deathMessageHandle(World &world, network::Message &msg)
    {
        size_t msgId = (unsigned char)msg[1] << 8U | (unsigned char)msg[2];

        auto &netIds = world.registry.getComponents<component::NetworkId>();

        for (size_t i = 0; i < netIds.size(); i++) {
            if (netIds[i])
                if (netIds[i].value().id == msgId) {
                    world.registry.killEntity(world.registry.entityFromIndex(i));
                    return;
                }
        }
        std::cerr << "Error: Client couldn't kill unknown entity with netId '" << msgId << "'." << std::endl;
    }

    static std::unordered_map<char, std::function<void(World &, network::Message &msg)>> packetTypeFunction = {
        {utils::constant::getPacketTypeKey(utils::constant::PacketType::ENTITY_MOVE), movePacketHandle},
        {0, firstMessageHandle},
        {utils::constant::getPacketTypeKey(utils::constant::PacketType::ENTITY_DEATH), deathMessageHandle}};

    bool packetTypeFunctionExists(char type)
    {
        for (auto &&i : packetTypeFunction) {
            if (i.first == type)
                return true;
        }
        return false;
    }

    std::function<void(World &)> HandleIncomingMessages = [](World &world) {
        while (!network::Client::getIncomingMessages().empty()) {
            network::Message msg = network::Client::getIncomingMessages().pop();
            if (packetTypeFunctionExists(msg[0]))
                packetTypeFunction[msg[0]](world, msg);
        }
    };
} // namespace ecs::systems
