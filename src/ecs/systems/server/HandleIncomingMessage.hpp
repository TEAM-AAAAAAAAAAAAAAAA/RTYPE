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
#include "Constant.hpp"
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
#include "components/server/Projectile.hpp"
#include "components/server/FollowEntity.hpp"
#include "components/server/AttackAI.hpp"

namespace ecs::systems
{
    /**
     * In goal of create a player, first, we need to add every components of the player.
     * Specify to the server that there is a new connection and check if the request has been accepted
     * @param world The world in which we want to operate
     * @param msg The message of a new player coming on the server
     */
    static void createPlayer(World &world, network::ClientMessage &msg)
    {
        ecs::Entity newPlayer = world.registry.spawn_entity();

        world.registry.addComponent<ecs::component::Position>(newPlayer, {50, utils::constant::mapHeight / 2});
        world.registry.addComponent<ecs::component::Velocity>(newPlayer, {5, 5});
        world.registry.addComponent<ecs::component::Size>(newPlayer, {32, 64});
        world.registry.addComponent<ecs::component::Direction>(newPlayer, {0, 0});
        world.registry.addComponent<ecs::component::EntityType>(newPlayer, {ecs::component::EntityType::Types::Player});
        world.registry.addComponent<ecs::component::Weapon>(newPlayer, {100, 50, 10, {20, 20}});
        world.registry.addComponent<ecs::component::Health>(newPlayer, {utils::constant::maxPlayerHealth});
        world.registry.addComponent<ecs::component::NetworkId>(newPlayer, {static_cast<size_t>(newPlayer)});
        world.registry.addComponent<ecs::component::Faction>(newPlayer, {ecs::component::Faction::Factions::Chefs});
        ecs::Entity playerBot = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::Position>(playerBot, {20, 5});
        world.registry.addComponent<ecs::component::Size>(playerBot, {16, 32});
        world.registry.addComponent<ecs::component::EntityType>(playerBot, {ecs::component::EntityType::Types::PlayerBot});
        world.registry.addComponent<ecs::component::Velocity>(playerBot, {0, 0});
        world.registry.addComponent<ecs::component::Direction>(playerBot, {0, 0});
        world.registry.addComponent<ecs::component::Health>(playerBot, {100});
        world.registry.addComponent<ecs::component::NetworkId>(playerBot, {static_cast<size_t>(playerBot)});
        world.registry.addComponent<ecs::component::Faction>(playerBot, {ecs::component::Faction::Factions::Chefs});
        world.registry.addComponent<ecs::component::FollowEntity>(playerBot, {static_cast<std::size_t>(newPlayer)});
        world.registry.addComponent<ecs::component::AttackAI>(playerBot, {component::AttackAI::AIType::PlayerBot});

        network::Server::getClientToEntID()[msg.second] = (size_t)newPlayer;
        network::Message message;
        message.fill(0);
        message[1] = static_cast<size_t>(newPlayer) >> 8;
        message[2] = static_cast<size_t>(newPlayer) & 0xFF;
        network::Server::getOutgoingMessages().push(network::ServerMessage(message, std::vector<unsigned int>()));
    }

    /**
     * Updating the player position according to the given msg
     * @param world The world we want to operate
     * @param msg The message containing the new position of the player
     */
    static void movePlayer(World &world, network::ClientMessage &msg)
    {
        auto &directions = world.registry.getComponents<component::Direction>();
        auto &networkIds = world.registry.getComponents<component::NetworkId>();

        for (size_t i = 0; i < directions.size() && i < networkIds.size(); ++i) {
            auto &dir = directions[i];
            auto &id = networkIds[i];

            if (dir && id) {
                if (network::Server::getClientToEntID()[msg.second] == id.value().id) {
                    dir.value().x = (int)msg.first[1];
                    dir.value().y = (int)msg.first[2];
                    return;
                }
            }
        }
    }

    /**
     * Used to make the player shoot from the given message
     * @param world The world we want to operate
     * @param msg Only used to compare ID and select the correct player
     */
    static void playerShoot(World &world, network::ClientMessage &msg)
    {
        auto &networkIds = world.registry.getComponents<component::NetworkId>();
        auto const &positions = world.registry.getComponents<component::Position>();
        auto &weapons = world.registry.getComponents<component::Weapon>();
        auto const &factions = world.registry.getComponents<component::Faction>();

        for (size_t i = 0; i < networkIds.size() && i < positions.size() && i < weapons.size() && i < factions.size();
             ++i) {
            auto &id = networkIds[i];

            if (id
                && network::Server::getClientToEntID().find(msg.second) != network::Server::getClientToEntID().end()
                    & network::Server::getClientToEntID()[msg.second] == id.value().id) {
                auto &pos = positions[i];
                auto &weapon = weapons[i];
                auto &fac = factions[i];

                if (pos && weapon && fac) {
                    auto elapsed = utils::constant::chrono::now().time_since_epoch().count() - weapon.value().lastShoot;
                    if (weapon.value().hasSuper && elapsed > weapon.value().superLoadingTime) {
                        weapon.value().lastShoot = utils::constant::chrono::now().time_since_epoch().count();
                    } else if (elapsed > weapon.value().shootDelay) {
                        weapon.value().lastShoot = utils::constant::chrono::now().time_since_epoch().count();
                        ecs::Entity bullet = world.registry.spawn_entity();
                        world.registry.addComponent<ecs::component::EntityType>(
                            bullet, {component::EntityType::Bullet});
                        world.registry.addComponent<ecs::component::NetworkId>(bullet, {static_cast<size_t>(bullet)});
                        world.registry.addComponent<ecs::component::Direction>(bullet, {1, 0});
                        world.registry.addComponent<ecs::component::Position>(bullet, {pos.value().x, pos.value().y});
                        world.registry.addComponent<ecs::component::Size>(
                            bullet, {weapon.value().projSize.first, weapon.value().projSize.second});
                        world.registry.addComponent<ecs::component::Velocity>(bullet, {weapon.value().projSpeed, 0});
                        world.registry.addComponent<ecs::component::Projectile>(bullet, {weapon.value().damage});
                        ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
                        if (i < factions.size() && factions[i])
                            fac = factions[i].value().faction;
                        world.registry.addComponent<ecs::component::Faction>(bullet, {fac});
                        world.registry.addComponent<ecs::component::Health>(bullet, {1});
                    }
                }
            }
        };
    }

    /**
     * Used send information about the room to the hub server
     * @param world Not used in this function
     * @param msg Only used to check packet type
     */
    static void sendRoomInfo(World &world, network::ClientMessage &msg)
    {
        network::ServerMessage message;

        message.first.fill(0);
        message.first[0] = 130;
        message.first[1] = network::Server::getClientCount() & 0xFF;
        message.second.push_back(msg.second);
        network::Server::getOutgoingMessages().push(message);
    }

    static void keepAliveResponse(World &world, network::ClientMessage &msg)
    {
        network::Message response;
        response[0] = 71;
        network::Server::getOutgoingMessages().push(std::pair(response, std::vector<unsigned int>()));
    }

    static std::unordered_map<char, std::function<void(World &, network::ClientMessage &msg)>> packetTypeFunction = {
        {0, createPlayer}, {utils::constant::PLAYER_MOVE, movePlayer}, {utils::constant::PLAYER_SHOT, playerShoot},
        {utils::constant::ROOM_INFO, sendRoomInfo}, {utils::constant::KEEP_ALIVE, keepAliveResponse}};

    std::function<void(World &)> HandleIncomingMessages = [](World &world) {
        while (!network::Server::getReceivedMessages().empty()) {
            network::ClientMessage msg = network::Server::getReceivedMessages().pop();
            if (packetTypeFunction.find(msg.first[0]) != packetTypeFunction.end())
                packetTypeFunction[msg.first[0]](world, msg);
        }
    };
} // namespace ecs::systems
