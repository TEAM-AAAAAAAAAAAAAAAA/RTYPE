/*
 * File: HandleSFMLMovements.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 10:11:08 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 10:16:24 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Controllable.hpp"

namespace ecs::systems
{
    std::function<void(World &)> handleSFMLMovements = [](World &world) {
        struct Movement {
            bool goUp;
            bool goLeft;
            bool goDown;
            bool goRight;
        };
        auto const &controllables = world.registry.getComponents<component::Controllable>();

        for (size_t i = 0; i < controllables.size(); ++i) {
            auto &contr = controllables[i];

            if (contr) {
                auto const con = contr.value();
                if (sf::Keyboard::isKeyPressed(con.MoveUp) || sf::Keyboard::isKeyPressed(con.MoveUpSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveUp));
                else if (sf::Keyboard::isKeyPressed(con.MoveLeft) || sf::Keyboard::isKeyPressed(con.MoveLeftSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveLeft));
                else if (sf::Keyboard::isKeyPressed(con.MoveDown) || sf::Keyboard::isKeyPressed(con.MoveDownSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveDown));
                else if (sf::Keyboard::isKeyPressed(con.MoveRight)
                    || sf::Keyboard::isKeyPressed(con.MoveRightSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveRight));
            }
        }
    };
}
