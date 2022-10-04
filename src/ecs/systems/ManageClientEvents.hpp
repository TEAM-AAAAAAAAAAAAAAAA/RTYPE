/*
 * File: ManageClientEvents.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 10:17:07 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 11:37:18 pm
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
#pragma endregion

            world.popEvent();
        }
    };
} // namespace ecs::systems
