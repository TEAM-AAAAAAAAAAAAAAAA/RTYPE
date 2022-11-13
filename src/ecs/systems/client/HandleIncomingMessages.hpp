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
#include "../client/AssetLoader.hpp"
#include "../client/NetworkClient.hpp"
#include "World.hpp"
#include "components/EntityType.hpp"
#include "components/NetworkId.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/client/Activable.hpp"
#include "components/client/Controllable.hpp"
#include "components/client/Drawable.hpp"
#include "components/client/Shootable.hpp"

namespace ecs::systems
{
    static size_t selfId = 0;
    static void movePacketHandle(World &world, network::Message &msg)
    {
        using AnimFrame = ecs::component::Animated::AnimFrame;

        std::cout << "UPDATE INFO SERVER\n";
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
        int sizeX = (unsigned char)msg[8] << 8U | (unsigned char)msg[9];
        int sizeY = (unsigned char)msg[10] << 8U | (unsigned char)msg[11];
        int velX = msg[12];
        int velY = msg[13];
        char dirX = msg[14];
        char dirY = msg[15];

        for (size_t i = 0; i < networkId.size(); i++)
            if (networkId[i] && networkId[i]->id == msgId) {
                if (i < sizes.size() && sizes[i]) {
                    sizes[i].value().width = sizeX;
                    sizes[i].value().height = sizeY;
                }
                if (i < positions.size() && positions[i]) {
                    positions[i].value().x = posX;
                    positions[i].value().y = posY;
                }
                if (i < types.size() && types[i]) {
                    types[i].value().type = type.type;
                }
                if (i < velocities.size() && velocities[i]) {
                    velocities[i].value().x = velX;
                    velocities[i].value().y = velY;
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
        world.registry.addComponent<component::Activable>(newEntity, {});
        switch (type.type) {
            case component::EntityType::Types::Player:
                if (msgId != selfId) {
                    world.registry.addComponent<component::EntityType>(
                            newEntity, {component::EntityType::Types::OtherPlayer});
                    world.registry.addComponent<component::Drawable>(newEntity, {"players", {1, 18, 32, 16}});
                    world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                          {AnimFrame(1, 18, 32, 16, 100), AnimFrame(34, 18, 32, 16, 100), AnimFrame(67, 18, 32, 16, 100),
                                                                           AnimFrame(100, 18, 32, 16, 100), AnimFrame(133, 18, 32, 16, 100),
                                                                           AnimFrame(100, 18, 32, 16, 100), AnimFrame(67, 18, 32, 16, 100),
                                                                           AnimFrame(34, 18, 32, 16, 100)});
                } else {
                    world.registry.addComponent<component::EntityType>(
                            newEntity, {component::EntityType::Types::Player});
                    world.registry.addComponent<ecs::component::Shootable>(
                            newEntity, ecs::component::Shootable(asset::AssetLoader::GetKeybind("shoot")));
                    world.registry.addComponent<ecs::component::Controllable>(newEntity,
                                                                              {asset::AssetLoader::GetKeybind("up"), asset::AssetLoader::GetKeybind("left"),
                                                                               asset::AssetLoader::GetKeybind("down"), asset::AssetLoader::GetKeybind("right"),
                                                                               asset::AssetLoader::GetKeybind("hitbox")});
                    world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                    world.registry.addComponent<component::Drawable>(newEntity, {"players", {1, 1, 32, 16}});
                    world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                          {AnimFrame(1, 1, 32, 16, 100), AnimFrame(34, 1, 32, 16, 100), AnimFrame(67, 1, 32, 16, 100),
                                                                           AnimFrame(100, 1, 32, 16, 100), AnimFrame(133, 1, 32, 16, 100),
                                                                           AnimFrame(100, 1, 32, 16, 100), AnimFrame(67, 1, 32, 16, 100),
                                                                           AnimFrame(34, 1, 32, 16, 100)});
                }
                break;
            case component::EntityType::Types::PlayerBot:
                world.registry.addComponent<component::EntityType>(
                        newEntity, {component::EntityType::Types::PlayerBot});
                world.registry.addComponent<component::Drawable>(newEntity, {"players", {1, 35, 32, 16}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(1, 35, 32, 16, 100), AnimFrame(34, 35, 32, 16, 100), AnimFrame(67, 35, 32, 16, 100),
                                                                       AnimFrame(100, 35, 32, 16, 100), AnimFrame(133, 35, 32, 16, 100),
                                                                       AnimFrame(100, 35, 32, 16, 100), AnimFrame(67, 35, 32, 16, 100),
                                                                       AnimFrame(34, 35, 32, 16, 100)});
                break;
#pragma region uranus ships
            case component::EntityType::Types::UranusBattlecruiser:
                world.registry.addComponent<component::Drawable>(newEntity, {"uranus-battlecruiser", {11, 26, 92, 76}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(11, 26, 92, 76, 100), AnimFrame(11, 154, 92, 76, 100), AnimFrame(11, 282, 92, 76, 100),
                                                                       AnimFrame(11, 410, 92, 76, 100), AnimFrame(11, 538, 92, 76, 100),
                                                                       AnimFrame(11, 666, 92, 76, 100), AnimFrame(11, 794, 92, 76, 100),
                                                                       AnimFrame(11, 922, 92, 76, 100), AnimFrame(11, 1050, 92, 76, 100),
                                                                       AnimFrame(11, 1178, 92, 76, 100), AnimFrame(11, 1306, 92, 76, 100),
                                                                       AnimFrame(11, 1434, 92, 76, 100), AnimFrame(11, 1562, 92, 76, 100),
                                                                       AnimFrame(11, 1690, 92, 76, 100), AnimFrame(11, 1818, 92, 76, 100),
                                                                       AnimFrame(11, 1946, 92, 76, 100), AnimFrame(11, 2074, 92, 76, 100),
                                                                       AnimFrame(11, 2202, 92, 76, 100), AnimFrame(11, 2330, 92, 76, 100),
                                                                       AnimFrame(11, 2458, 92, 76, 100), AnimFrame(11, 2586, 92, 76, 100),
                                                                       AnimFrame(11, 2714, 92, 76, 100), AnimFrame(11, 2842, 92, 76, 100),
                                                                       AnimFrame(11, 2970, 92, 76, 100), AnimFrame(11, 3098, 92, 76, 100),
                                                                       AnimFrame(11, 3226, 92, 76, 100), AnimFrame(11, 3354, 92, 76, 100),
                                                                       AnimFrame(11, 3482, 92, 76, 100), AnimFrame(11, 3610, 92, 76, 100)});
                break;
            case component::EntityType::Types::UranusDreadnought:
                world.registry.addComponent<component::Drawable>(newEntity, {"uranus-dreadnought", {11, 26, 104, 76}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(
                        newEntity, {AnimFrame(11, 26, 104, 76, 100), AnimFrame(11, 154, 104, 76, 100)});
                break;
            case component::EntityType::Types::UranusFighter:
                world.registry.addComponent<component::Drawable>(newEntity, {"uranus-fighter", {20, 20, 24, 24}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(20, 20, 24, 24, 100), AnimFrame(20, 84, 24, 24, 100), AnimFrame(20, 148, 24, 24, 100),
                                                                       AnimFrame(20, 212, 24, 24, 100), AnimFrame(20, 276, 24, 24, 100)});
                break;
            case component::EntityType::Types::UranusFrigate:
                world.registry.addComponent<component::Drawable>(newEntity, {"uranus-frigate", {9, 12, 42, 40}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(9, 12, 42, 40, 100), AnimFrame(9, 76, 42, 40, 100), AnimFrame(9, 140, 42, 40, 100),
                                                                       AnimFrame(9, 204, 42, 40, 100), AnimFrame(9, 268, 42, 40, 100)});
                break;
            case component::EntityType::Types::UranusScout:
                world.registry.addComponent<component::Drawable>(newEntity, {"uranus-scout", {21, 20, 24, 24}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(21, 20, 24, 24, 100), AnimFrame(21, 84, 24, 24, 100), AnimFrame(21, 148, 24, 24, 100),
                                                                       AnimFrame(21, 212, 24, 24, 100), AnimFrame(21, 276, 24, 24, 100)});
                break;
            case component::EntityType::Types::UranusTorpedo:
                world.registry.addComponent<component::Drawable>(newEntity, {"uranus-torpedo", {14, 2, 30, 60}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(14, 2, 30, 60, 100), AnimFrame(14, 66, 30, 60, 100), AnimFrame(14, 130, 30, 60, 100),
                                                                       AnimFrame(14, 194, 30, 60, 100), AnimFrame(14, 258, 30, 60, 100),
                                                                       AnimFrame(14, 322, 30, 60, 100), AnimFrame(14, 386, 30, 60, 100),
                                                                       AnimFrame(14, 450, 30, 60, 100), AnimFrame(14, 514, 30, 60, 100),
                                                                       AnimFrame(14, 578, 30, 60, 100), AnimFrame(14, 642, 30, 60, 100),
                                                                       AnimFrame(14, 706, 30, 60, 100), AnimFrame(14, 770, 30, 60, 100),
                                                                       AnimFrame(14, 834, 30, 60, 100), AnimFrame(14, 898, 30, 60, 100),
                                                                       AnimFrame(14, 962, 30, 60, 100)});
                break;
#pragma endregion
#pragma region janitor ships
            case component::EntityType::Types::JanitorBattlecruiser:
                world.registry.addComponent<component::Drawable>(
                        newEntity, {"janitor-battlecruiser", {12, 31, 90, 66}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(12, 31, 90, 66, 100), AnimFrame(12, 159, 90, 66, 100), AnimFrame(12, 287, 90, 66, 100),
                                                                       AnimFrame(12, 415, 90, 66, 100), AnimFrame(12, 543, 90, 66, 100),
                                                                       AnimFrame(12, 671, 90, 66, 100), AnimFrame(12, 799, 90, 66, 100),
                                                                       AnimFrame(12, 927, 90, 66, 100), AnimFrame(12, 1055, 90, 66, 100)});
                break;
            case component::EntityType::Types::JanitorDreadnought:
                world.registry.addComponent<component::Drawable>(newEntity, {"janitor-dreadnought", {11, 28, 102, 72}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(11, 28, 102, 72, 100), AnimFrame(11, 156, 102, 72, 100),
                                                                       AnimFrame(11, 284, 102, 72, 100), AnimFrame(11, 412, 102, 72, 100),
                                                                       AnimFrame(11, 540, 102, 72, 100), AnimFrame(11, 668, 102, 72, 100),
                                                                       AnimFrame(11, 796, 102, 72, 100), AnimFrame(11, 924, 102, 72, 100),
                                                                       AnimFrame(11, 1052, 102, 72, 100), AnimFrame(11, 1180, 102, 72, 100),
                                                                       AnimFrame(11, 1308, 102, 72, 100), AnimFrame(11, 1436, 102, 72, 100)});
                break;
            case component::EntityType::Types::JanitorFighter:
                world.registry.addComponent<component::Drawable>(newEntity, {"janitor-fighter", {17, 16, 32, 32}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(17, 16, 32, 32, 100), AnimFrame(17, 80, 32, 32, 100), AnimFrame(17, 144, 32, 32, 100),
                                                                       AnimFrame(17, 208, 32, 32, 100), AnimFrame(17, 272, 32, 32, 100),
                                                                       AnimFrame(17, 336, 32, 32, 100), AnimFrame(17, 400, 32, 32, 100),
                                                                       AnimFrame(17, 464, 32, 32, 100), AnimFrame(17, 528, 32, 32, 100),
                                                                       AnimFrame(17, 592, 32, 32, 100), AnimFrame(17, 656, 32, 32, 100),
                                                                       AnimFrame(17, 720, 32, 32, 100), AnimFrame(17, 784, 32, 32, 100),
                                                                       AnimFrame(17, 848, 32, 32, 100), AnimFrame(17, 912, 32, 32, 100),
                                                                       AnimFrame(17, 976, 32, 32, 100), AnimFrame(17, 1040, 32, 32, 100),
                                                                       AnimFrame(17, 1104, 32, 32, 100), AnimFrame(17, 1168, 32, 32, 100),
                                                                       AnimFrame(17, 1232, 32, 32, 100), AnimFrame(17, 1296, 32, 32, 100),
                                                                       AnimFrame(17, 1360, 32, 32, 100), AnimFrame(17, 1424, 32, 32, 100),
                                                                       AnimFrame(17, 1488, 32, 32, 100), AnimFrame(17, 1552, 32, 32, 100),
                                                                       AnimFrame(17, 1616, 32, 32, 100), AnimFrame(17, 1680, 32, 32, 100),
                                                                       AnimFrame(17, 1744, 32, 32, 100)});
                break;
            case component::EntityType::Types::JanitorFrigate:
                world.registry.addComponent<component::Drawable>(newEntity, {"janitor-frigate", {6, 8, 48, 48}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(6, 8, 48, 48, 100), AnimFrame(6, 72, 48, 48, 100), AnimFrame(6, 136, 48, 48, 100),
                                                                       AnimFrame(6, 200, 48, 48, 100), AnimFrame(6, 264, 48, 48, 100)});
                break;
            case component::EntityType::Types::JanitorScout:
                world.registry.addComponent<component::Drawable>(newEntity, {"janitor-scout", {20, 18, 28, 28}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(20, 18, 28, 28, 100), AnimFrame(20, 82, 28, 28, 100), AnimFrame(20, 146, 28, 28, 100),
                                                                       AnimFrame(20, 210, 28, 28, 100), AnimFrame(20, 274, 28, 28, 100),
                                                                       AnimFrame(20, 338, 28, 28, 100)});
                break;
            case component::EntityType::Types::JanitorTorpedo:
                world.registry.addComponent<component::Drawable>(newEntity, {"janitor-torpedo", {17, 4, 32, 56}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(17, 4, 32, 56, 100), AnimFrame(17, 68, 32, 56, 100), AnimFrame(17, 132, 32, 56, 100),
                                                                       AnimFrame(17, 196, 32, 56, 100), AnimFrame(17, 260, 32, 56, 100),
                                                                       AnimFrame(17, 324, 32, 56, 100), AnimFrame(17, 388, 32, 56, 100),
                                                                       AnimFrame(17, 452, 32, 56, 100), AnimFrame(17, 516, 32, 56, 100),
                                                                       AnimFrame(17, 580, 32, 56, 100), AnimFrame(17, 644, 32, 56, 100),
                                                                       AnimFrame(17, 708, 32, 56, 100)});
                break;
#pragma endregion
#pragma region alien ships
            case component::EntityType::Types::AlienBattlecruiser:
                world.registry.addComponent<component::Drawable>(newEntity, {"alien-battlecruiser", {18, 26, 94, 76}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(18, 26, 94, 76, 100), AnimFrame(18, 154, 94, 76, 100), AnimFrame(18, 282, 94, 76, 100),
                                                                       AnimFrame(18, 410, 94, 76, 100), AnimFrame(18, 538, 94, 76, 100),
                                                                       AnimFrame(18, 666, 94, 76, 100), AnimFrame(18, 794, 94, 76, 100),
                                                                       AnimFrame(18, 922, 94, 76, 100), AnimFrame(18, 1050, 94, 76, 100)});
                break;
            case component::EntityType::Types::AlienDreadnought:
                world.registry.addComponent<component::Drawable>(newEntity, {"alien-dreadnought", {16, 26, 102, 76}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(16, 26, 102, 76, 100), AnimFrame(16, 154, 102, 76, 100),
                                                                       AnimFrame(16, 282, 102, 76, 100), AnimFrame(16, 410, 102, 76, 100),
                                                                       AnimFrame(16, 538, 102, 76, 100), AnimFrame(16, 666, 102, 76, 100),
                                                                       AnimFrame(16, 794, 102, 76, 100), AnimFrame(16, 922, 102, 76, 100),
                                                                       AnimFrame(16, 1050, 102, 76, 100)});
                break;
            case component::EntityType::Types::AlienFighter:
                world.registry.addComponent<component::Drawable>(newEntity, {"alien-fighter", {15, 14, 32, 36}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(15, 14, 32, 36, 100), AnimFrame(15, 78, 32, 36, 100), AnimFrame(15, 142, 32, 36, 100),
                                                                       AnimFrame(15, 206, 32, 36, 100), AnimFrame(15, 270, 32, 36, 100),
                                                                       AnimFrame(15, 334, 32, 36, 100), AnimFrame(15, 398, 32, 36, 100),
                                                                       AnimFrame(15, 462, 32, 36, 100), AnimFrame(15, 526, 32, 36, 100)});
                break;
            case component::EntityType::Types::AlienFrigate:
                world.registry.addComponent<component::Drawable>(newEntity, {"alien-frigate", {11, 8, 40, 48}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(11, 8, 40, 48, 100), AnimFrame(11, 72, 40, 48, 100), AnimFrame(11, 136, 40, 48, 100),
                                                                       AnimFrame(11, 200, 40, 48, 100), AnimFrame(11, 264, 40, 48, 100),
                                                                       AnimFrame(11, 328, 40, 48, 100), AnimFrame(11, 392, 40, 48, 100),
                                                                       AnimFrame(11, 456, 40, 48, 100), AnimFrame(11, 520, 40, 48, 100)});
                break;
            case component::EntityType::Types::AlienScout:
                world.registry.addComponent<component::Drawable>(newEntity, {"alien-scout", {19, 14, 32, 36}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(19, 14, 32, 36, 100), AnimFrame(19, 78, 32, 36, 100), AnimFrame(19, 142, 32, 36, 100),
                                                                       AnimFrame(19, 206, 32, 36, 100), AnimFrame(19, 270, 32, 36, 100),
                                                                       AnimFrame(19, 334, 32, 36, 100), AnimFrame(19, 398, 32, 36, 100)});
                break;
            case component::EntityType::Types::AlienTorpedo:
                world.registry.addComponent<component::Drawable>(newEntity, {"alien-torpedo", {14, 2, 30, 60}});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                world.registry.addComponent<ecs::component::Animated>(newEntity,
                                                                      {AnimFrame(16, 2, 30, 60, 100), AnimFrame(16, 66, 30, 60, 100), AnimFrame(16, 130, 30, 60, 100),
                                                                       AnimFrame(16, 194, 30, 60, 100), AnimFrame(16, 258, 30, 60, 100),
                                                                       AnimFrame(16, 322, 30, 60, 100), AnimFrame(16, 386, 30, 60, 100),
                                                                       AnimFrame(16, 450, 30, 60, 100), AnimFrame(16, 514, 30, 60, 100),
                                                                       AnimFrame(16, 578, 30, 60, 100), AnimFrame(16, 642, 30, 60, 100),
                                                                       AnimFrame(16, 706, 30, 60, 100), AnimFrame(16, 770, 30, 60, 100),
                                                                       AnimFrame(16, 834, 30, 60, 100), AnimFrame(16, 898, 30, 60, 100),
                                                                       AnimFrame(16, 962, 30, 60, 100)});
                break;
            case component::EntityType::Types::NoodleMonster:
                world.registry.addComponent<component::Drawable>(newEntity, {"noodle-monster"});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
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
            case component::EntityType::Types::EnergySphere:
                world.registry.addComponent<component::Drawable>(newEntity,
                                                                 {"energy-sphere", {0, 0, 32, 32},
                                                                  std::atan2(static_cast<float>(dirX), static_cast<float>(dirY)) * 180 / 3.14159265359f});
                world.registry.addComponent<component::Animated>(newEntity,
                                                                 {AnimFrame(0, 0, 32, 32, 100), AnimFrame(32, 0, 32, 32, 100), AnimFrame(64, 0, 32, 32, 100),
                                                                  AnimFrame(96, 0, 32, 32, 100), AnimFrame(128, 0, 32, 32, 100), AnimFrame(160, 0, 32, 32, 100),
                                                                  AnimFrame(192, 0, 32, 32, 100), AnimFrame(224, 0, 32, 32, 100), AnimFrame(256, 0, 32, 32, 100),
                                                                  AnimFrame(288, 0, 32, 32, 100)});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                break;
            case component::EntityType::Types::Laser:
                world.registry.addComponent<component::Drawable>(newEntity,
                                                                 {"laser", {0, 13, 32, 6},
                                                                  std::atan2(static_cast<float>(dirX), static_cast<float>(dirY)) * 180 / 3.14159265359f});
                world.registry.addComponent<component::Animated>(newEntity,
                                                                 {AnimFrame(0, 13, 32, 6, 100), AnimFrame(0, 45, 32, 6, 100), AnimFrame(0, 77, 32, 6, 100),
                                                                  AnimFrame(0, 109, 32, 6, 100), AnimFrame(0, 141, 32, 6, 100)});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                break;
            case component::EntityType::Types::Rocket:
                world.registry.addComponent<component::Drawable>(newEntity,
                                                                 {"rocket", {12, 9, 7, 20},
                                                                  std::atan2(static_cast<float>(dirX), static_cast<float>(dirY)) * 180 / 3.14159265359f});
                world.registry.addComponent<component::Animated>(newEntity,
                                                                 {AnimFrame(12, 9, 7, 20, 100), AnimFrame(44, 9, 7, 20, 100), AnimFrame(79, 9, 7, 20, 100)});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                break;
            case component::EntityType::Types::Asteroid:
                world.registry.addComponent<component::Drawable>(newEntity,
                                                                 {"asteroid", {29, 32, 38, 33},
                                                                  std::atan2(static_cast<float>(dirX), static_cast<float>(dirY)) * 180 / 3.14159265359f});
                world.registry.addComponent<ecs::component::Hitbox>(newEntity, {ecs::component::Hitbox()});
                break;
        }
    }
#pragma endregion
    static void firstMessageHandle(World &world, network::Message &msg)
    {
        if (selfId == 0)
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
    }

    static void playerHealthHandle(World &world, network::Message &msg)
    {
        size_t msgId = (unsigned char)msg[1] << 8U | (unsigned char)msg[2];
        auto &netIds = world.registry.getComponents<component::NetworkId>();
        auto &healths = world.registry.getComponents<component::Health>();

        for (size_t i = 0; i < netIds.size(); i++) {
            if (netIds[i]) {
                if (netIds[i].value().id == msgId) {
                    for (size_t j = 0; j < healths.size(); j++)
                        if (healths[j])
                            healths[j].value().health = msg[3];
                    return;
                }
            }
        }
    }

    static void roomUpdate(World &world, network::Message &msg)
    {
        auto &texts = world.registry.getComponents<component::Text>();
        auto &activables = world.registry.getComponents<component::Activable>();
        auto &positions = world.registry.getComponents<component::Position>();
        auto &connections = world.registry.getComponents<component::Connection>();
        int port = (unsigned char)msg[1] << 8U | (unsigned char)msg[2];
        int nbPlayer = (unsigned char)msg[3];

        for (size_t i = 0; i < activables.size() && i < positions.size() && i < connections.size(); i++) {
            auto &pos = positions[i];
            auto &activ = activables[i];
            auto &connec = connections[i];

            if (pos && activ && connec) {
                if (activ->getButtonType() == utils::constant::ROOM) {
                    if (!connec->getIsSet()) {
                        connec->setPort(port);
                        for (size_t j = 0; j < texts.size() && j < activables.size(); j++)
                            if (activables[j]->getButtonType() == utils::constant::ROOM_TEXT && !texts[j]->getIsSet()) {
                                texts[j]->setContent(0, std::to_string(nbPlayer));
                                texts[j]->setContent(3, std::to_string(port));
                                texts[j]->setIsSet(true);
                                return;
                            }
                    }
                }
            }
        }
    }

    static void keepAliveResponse(World &world, network::Message &msg)
    {
        network::Message response;
        response[0] = 71;
        network::Client::getOutgoingMessages().push(response);
    }

    static std::unordered_map<char, std::function<void(World &, network::Message &msg)>> packetTypeFunction = {
            {utils::constant::getPacketTypeKey(utils::constant::PacketType::ENTITY_MOVE), movePacketHandle},
            {0, firstMessageHandle},
            {utils::constant::getPacketTypeKey(utils::constant::PacketType::ENTITY_DEATH), deathMessageHandle},
            {utils::constant::getPacketTypeKey(utils::constant::PacketType::KEEP_ALIVE), keepAliveResponse},
            {utils::constant::getPacketTypeKey(utils::constant::PacketType::ROOM_UPDATE), roomUpdate},
            {utils::constant::getPacketTypeKey(utils::constant::PacketType::HEALTH_UPDATE), playerHealthHandle}};

    std::function<void(World &)> HandleIncomingMessages = [](World &world) {
        while (!network::Client::getReceivedMessages().empty()) {
            network::Message msg = network::Client::getReceivedMessages().pop();
            if (packetTypeFunction.find(msg[0]) != packetTypeFunction.end())
                packetTypeFunction[msg[0]](world, msg);
        }
    };
} // namespace ecs::systems
