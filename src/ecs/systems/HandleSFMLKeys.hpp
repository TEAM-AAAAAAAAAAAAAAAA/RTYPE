/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleSFMLKeys
*/

#pragma once

#include <functional>
#include "World.hpp"
#include "components/Controllable.hpp"
#include "components/Shootable.hpp"

namespace ecs::systems
{
    /**
     * Used to manage every action ordered by Sfml input by the user
     * Refer to the Controllable.hpp documentation to learn more about managed input
     */
    std::function<void(World &)> handleSFMLKeys = [](World &world) {
#ifdef CLIENT_COMPILATION_MODE
        auto const &controllables = world.registry.getComponents<component::Controllable>();
        // auto const &shootables = world.registry.getComponents<component::Shootable>();

        for (const auto &contr : controllables) {
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
#endif
    };
} // namespace ecs::systems
