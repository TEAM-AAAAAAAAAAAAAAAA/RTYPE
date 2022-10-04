/*
 * File: ManageClientEvents.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 10:17:07 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Wednesday, 5th October 2022 12:44:25 am
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include "Event.hpp"
#include "World.hpp"
#include "components/Controllable.hpp"
#include "components/Direction.hpp"

namespace ecs::systems
{
    std::function<void(World &)> manageClientEvents = [](World &world) {
        while (world.getEvent() != ecs::Event::EventType::Null) {

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
                            dir.value().y -= 1;
                        else if (world.getEvent() == ecs::Event::EventType::MoveLeft)
                            dir.value().x -= 1;
                        else if (world.getEvent() == ecs::Event::EventType::MoveDown)
                            dir.value().y += 1;
                        else if (world.getEvent() == ecs::Event::EventType::MoveRight)
                            dir.value().x += 1;
                        if (dir.value().x > 0)
                            dir.value().x = 1;
                        else if (dir.value().x < 0)
                            dir.value().x = -1;
                        if (dir.value().y > 0)
                            dir.value().y = 1;
                        else if (dir.value().y < 0)
                            dir.value().y = -1;
                    }
                };
            }
#pragma endregion

#pragma region Bullet Shoot
            else if (world.getEvent() == ecs::Event::EventType::Shoot) {
                auto const &controllables = world.registry.getComponents<component::Controllable>();
                auto const &positions = world.registry.getComponents<component::Position>();

                for (size_t i = 0; i < positions.size() && i < controllables.size(); ++i) {
                    auto const &pos = positions[i];
                    auto const &con = controllables[i];
                    if (pos && con) {
                        ecs::Entity bullet = world.registry.spawn_entity();
                        world.registry.addComponent<ecs::component::Direction>(bullet, {1, 0});
                        world.registry.addComponent<ecs::component::Drawable>(
                            bullet, {"src/demo/assets/textures/players.gif", {5, 5, 1, 1}});
                        world.registry.addComponent<ecs::component::Position>(bullet, {pos.value().x, pos.value().y});
                        world.registry.addComponent<ecs::component::Size>(bullet, {10, 10});
                        world.registry.addComponent<ecs::component::Velocity>(bullet, {10, 0});
                    }
                }
            }
#pragma endregion

            world.popEvent();
        }
    };
} // namespace ecs::systems
