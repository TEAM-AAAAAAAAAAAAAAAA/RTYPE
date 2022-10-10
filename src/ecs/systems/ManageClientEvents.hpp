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
#include "components/Controllable.hpp"
#include "components/Direction.hpp"
#include "components/Projectile.hpp"
#include "components/Weapon.hpp"

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
                || world.getEvent() == ecs::Event::EventType::MoveRight) {
                auto &directions = world.registry.getComponents<component::Direction>();
                auto const &controllables = world.registry.getComponents<component::Controllable>();

                for (size_t i = 0; i < directions.size() && i < controllables.size(); ++i) {
                    auto &dir = directions[i];
                    auto const &con = controllables[i];
                    if (dir && con) {
                        if (world.getEvent() == ecs::Event::EventType::MoveUp)
                            dir.value().y <= 0 ? dir.value().y = -1 : dir.value().y -= 1;
                        else if (world.getEvent() == ecs::Event::EventType::MoveLeft)
                            dir.value().x <= 0 ? dir.value().x = -1 : dir.value().x -= 1;
                        else if (world.getEvent() == ecs::Event::EventType::MoveDown)
                            dir.value().y >= 0 ? dir.value().y = 1 : dir.value().y += 1;
                        else if (world.getEvent() == ecs::Event::EventType::MoveRight)
                            dir.value().x >= 0 ? dir.value().x = 1 : dir.value().x += 1;
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
                auto const &controllables = world.registry.getComponents<component::Controllable>();
                auto const &positions = world.registry.getComponents<component::Position>();
                auto &weapons = world.registry.getComponents<component::Weapon>();

                for (size_t i = 0; i < positions.size() && i < controllables.size(); ++i) {
                    auto const &pos = positions[i];
                    auto const &con = controllables[i];
                    auto &weapon = weapons[i];
                    if (pos && con && weapon) {
                        auto elapsed = chrono::now().time_since_epoch().count() - weapon.value().LastShoot;
                        if (weapon.value().HasSuper && elapsed > weapon.value().SuperLoadingTime) {
                            weapon.value().LastShoot = chrono::now().time_since_epoch().count();
                            // spawn super bullet
                        } else if (elapsed > weapon.value().ShootDelay) {
                            weapon.value().LastShoot = chrono::now().time_since_epoch().count();
                            ecs::Entity bullet = world.registry.spawn_entity();
                            world.registry.addComponent<ecs::component::Direction>(bullet, {1, 0});
                            world.registry.addComponent<ecs::component::Position>(
                                bullet, {pos.value().x, pos.value().y});
                            world.registry.addComponent<ecs::component::Size>(bullet, {10, 10});
                            world.registry.addComponent<ecs::component::Velocity>(bullet, {10, 0});
                            world.registry.addComponent<ecs::component::Projectile>(bullet, {weapon.value().Damage});
#ifdef CLIENT_COMPILATION_MODE
                            std::filesystem::path playerPath =
                                ecs::crossPlatformPath("src", "demo", "assets", "textures", "players.gif");
                            world.registry.addComponent<ecs::component::Drawable>(
                                bullet, {playerPath, {5, 5, 1, 1}}); // To be removed with the server/client split
#endif
                        }
                    }
                }
            }
#pragma endregion

            world.popEvent();
        }
    };
} // namespace ecs::systems
