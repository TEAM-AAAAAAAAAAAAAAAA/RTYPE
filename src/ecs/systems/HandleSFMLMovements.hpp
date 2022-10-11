/*
 * File: HandleSFMLMovements.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 10:11:08 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Wednesday, 5th October 2022 2:07:45 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include "World.hpp"
#include "components/Controllable.hpp"

namespace ecs::systems
{
    /**
     * Used to manage every movement ordered by Sfml input by the user
     * Refer to the Controllable.hpp documentation to learn more about managed input
     */
    std::function<void(World &)> handleSFMLMovements = [](World &world) {
        auto const &controllables = world.registry.getComponents<component::Controllable>();

        for (size_t i = 0; i < controllables.size(); ++i) {
            auto const &contr = controllables[i];

            if (contr) {
                if (sf::Keyboard::isKeyPressed(contr.value().MoveUp)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveUpSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveUp));
                if (sf::Keyboard::isKeyPressed(contr.value().MoveLeft)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveLeftSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveLeft));
                if (sf::Keyboard::isKeyPressed(contr.value().MoveDown)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveDownSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveDown));
                if (sf::Keyboard::isKeyPressed(contr.value().MoveRight)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveRightSecondary))
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveRight));
            }
        }
    };
} // namespace ecs::systems
