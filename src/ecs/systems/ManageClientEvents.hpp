/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** ManageClientEvents
*/

#pragma once

#include <functional>
#include "Event.hpp"
#include "World.hpp"
#include "components/Direction.hpp"
#include "components/Faction.hpp"
#include "components/Weapon.hpp"
#include "components/client/Controllable.hpp"
#include "components/server/Projectile.hpp"
#include "../client/NetworkClient.hpp"
#include "Constant.hpp"

namespace ecs::systems
{
    /**
     * Used to manage every client' events
     * Refer to SFMLEvents.hpp documentation to learn more about managed events
     */
    std::function<void(World &)> manageClientEvents = [](World &world) {
        while (world.getEvent() != ecs::Event::EventType::Null) {

/**
 * Region only reserved for player movement.
 * Incrementing and decrementing the entity direction is used to manage multi input in the sametime, still caped as
 * 1 or -1
 */
#pragma region Player Movement
            if (world.getEvent() == ecs::Event::EventType::MoveUp || world.getEvent() == ecs::Event::EventType::MoveLeft
                || world.getEvent() == ecs::Event::EventType::MoveDown
                || world.getEvent() == ecs::Event::EventType::MoveRight || world.getEvent() == ecs::Event::EventType::MoveStop) {
                auto &directions = world.registry.getComponents<component::Direction>();
                auto &controllables = world.registry.getComponents<component::Controllable>();

                for (size_t i = 0; i < directions.size() && i < controllables.size(); ++i) {
                    auto &dir = directions[i];
                    auto &con = controllables[i];
                    if (dir && con) {
                        int x = dir.value().x;
                        int y = dir.value().y;
                        if (world.getEvent() == ecs::Event::EventType::MoveStop) {
                            dir.value().x = 0;
                            dir.value().y = 0;
                        } else if (world.getEvent() == ecs::Event::EventType::MoveUp) {
                            dir.value().y = -1;
                            // dir.value().y <= 0 ? dir.value().y = -1 : dir.value().y -= 1;
                        } else if (world.getEvent() == ecs::Event::EventType::MoveLeft) {
                            dir.value().x = -1;
                            // dir.value().x <= 0 ? dir.value().x = -1 : dir.value().x -= 1;
                        } else if (world.getEvent() == ecs::Event::EventType::MoveDown) {
                            dir.value().y = 1;
                            // dir.value().y >= 0 ? dir.value().y = 1 : dir.value().y += 1;
                        } else if (world.getEvent() == ecs::Event::EventType::MoveRight) {
                            dir.value().x = 1;
                            // dir.value().x >= 0 ? dir.value().x = 1 : dir.value().x += 1;
                        }
                        std::cout << dir.value().x << " " << dir.value().y << std::endl;
                        std::cout << x << " " << y << std::endl;
                        if (x != dir.value().x || y != dir.value().y)
                            dir.value().hasMoved = true;
                    }
                }
            }
#pragma endregion

/**
 * Region only reserved for bullet Shoot
 * If the system is called, instantly create a new entity with bullet's component
 */
#pragma region Bullet Shoot
            else if (world.getEvent() == ecs::Event::EventType::Shoot) {
                std::cout << "SHOOOOOOOOOOOOOOOOOT" << std::endl;
                network::Message msg;
                msg.fill(0);
                msg.at(0) = constant::getPacketTypeKey(ecs::constant::PacketType::PLAYER_SHOT);
                network::Client::getOutgoingMessages().push(msg);
            }
//                 auto const &controllables = world.registry.getComponents<component::Controllable>();
//                 auto const &positions = world.registry.getComponents<component::Position>();
//                 auto &weapons = world.registry.getComponents<component::Weapon>();
//                 auto const &factions = world.registry.getComponents<component::Faction>();

//                 for (size_t i = 0; i < positions.size() && i < controllables.size(); ++i) {
//                     auto const &pos = positions[i];
//                     auto const &con = controllables[i];
//                     auto &weapon = weapons[i];
//                     if (pos && con && weapon) {
//                         auto elapsed = constant::chrono::now().time_since_epoch().count() - weapon.value().lastShoot;
//                         if (weapon.value().hasSuper && elapsed > weapon.value().superLoadingTime) {
//                             weapon.value().lastShoot = constant::chrono::now().time_since_epoch().count();
//                             // spawn super bullet
//                         } else if (elapsed > weapon.value().shootDelay) {
//                             weapon.value().lastShoot = constant::chrono::now().time_since_epoch().count();
//                             ecs::Entity bullet = world.registry.spawn_entity();
//                             world.registry.addComponent<ecs::component::Direction>(bullet, {1, 0});
//                             world.registry.addComponent<ecs::component::Position>(
//                                 bullet, {pos.value().x, pos.value().y});
//                             world.registry.addComponent<ecs::component::Size>(bullet, {10, 10});
//                             world.registry.addComponent<ecs::component::Velocity>(bullet, {weapon.value().projSpeed, 0});
//                             world.registry.addComponent<ecs::component::Projectile>(bullet, {weapon.value().damage});
//                             ecs::component::Faction::Factions fac = ecs::component::Faction::Factions::None;
//                             if (i < factions.size() && factions[i])
//                                 fac = factions[i].value().faction;
//                             world.registry.addComponent<ecs::component::Faction>(bullet, {fac});
// #ifdef CLIENT_COMPILATION_MODE
//                             std::filesystem::path playerPath =
//                                 ecs::crossPlatformPath("src", "demo", "assets", "textures", "players.gif");
//                             world.registry.addComponent<ecs::component::Drawable>(
//                                 bullet, {playerPath, {5, 5, 1, 1}}); // To be removed with the server/client split
// #endif
//                         }
//                     }
//                 }
//             }
#pragma endregion

            world.popEvent();
        }
    };
} // namespace ecs::systems
