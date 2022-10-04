/*
 * File: handleSFMLKeys.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 10:11:08 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Wednesday, 5th October 2022 12:42:26 am
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include "World.hpp"
#include "components/Controllable.hpp"
#include "components/Shootable.hpp"

namespace ecs::systems
{
    std::function<void(World &)> handleSFMLKeys = [](World &world) {
        auto const &controllables = world.registry.getComponents<component::Controllable>();
        // auto const &shootables = world.registry.getComponents<component::Shootable>();

        for (size_t i = 0; i < controllables.size(); ++i) {
            auto &contr = controllables[i];
            // auto &shoot = shootables[i];

            if (contr) {
                if (sf::Keyboard::isKeyPressed(contr.value().MoveUp)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveUpSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveUp));
                else if (sf::Keyboard::isKeyPressed(contr.value().MoveDown)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveDownSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveDown));
                if (sf::Keyboard::isKeyPressed(contr.value().MoveLeft)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveLeftSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveLeft));
                else if (sf::Keyboard::isKeyPressed(contr.value().MoveRight)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveRightSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveRight));

                // if (shoot) {
                //     if (sf::Keyboard::isKeyPressed(shoot.value().Shoot)
                //         || sf::Keyboard::isKeyPressed(shoot.value().ShootSecondary))
                //         world.pushEvent(ecs::Event(ecs::Event::EventType::Shoot));
                // }
            }
        }
    };
}
