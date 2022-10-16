/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleSFMLKeys
*/

#pragma once

#include <functional>
#include "World.hpp"
#include "components/client/Controllable.hpp"
#include "components/client/Shootable.hpp"

namespace ecs::systems
{
    /**
     * Used to manage every action ordered by Sfml input by the user
     * Refer to the Controllable.hpp documentation to learn more about managed input
     */
    std::function<void(World &)> handleSFMLKeys = [](World &world) {
#ifdef CLIENT_COMPILATION_MODE
        auto &controllables = world.registry.getComponents<component::Controllable>();
        auto const &shootables = world.registry.getComponents<component::Shootable>();

        for (size_t i = 0; i < controllables.size() && i < shootables.size(); ++i) {
            auto &contr = controllables[i];
            auto const &shoot = shootables[i];

            if (contr) {
                bool hasMoved = false;
                static ecs::Event::EventType lastEvent;

                if (sf::Keyboard::isKeyPressed(contr.value().MoveUp)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveUpSecondary)) {
                    hasMoved = true;
                    // if (lastEvent != ecs::Event(ecs::Event::EventType::MoveUp)) {
                        world.pushEvent(ecs::Event(ecs::Event::EventType::MoveUp));
                        lastEvent = ecs::Event::EventType::MoveUp;
                    // }
                    // contr.value().lastDirectionY = ecs::Event::EventType::MoveUp;
                } else if (sf::Keyboard::isKeyPressed(contr.value().MoveDown)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveDownSecondary)) {
                    hasMoved = true;
                    // if (lastEvent != ecs::Event(ecs::Event::EventType::MoveDown)) {
                        world.pushEvent(ecs::Event(ecs::Event::EventType::MoveDown));
                        lastEvent = ecs::Event::EventType::MoveDown;
                    // }
                    // contr.value().lastDirectionY = ecs::Event::EventType::MoveDown;
                }
                if (sf::Keyboard::isKeyPressed(contr.value().MoveLeft)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveLeftSecondary)) {
                    hasMoved = true;
                    // if (lastEvent != ecs::Event(ecs::Event::EventType::MoveLeft)) {
                        world.pushEvent(ecs::Event(ecs::Event::EventType::MoveLeft));
                        lastEvent = ecs::Event::EventType::MoveLeft;
                    // }
                    // contr.value().lastDirectionX = ecs::Event::EventType::MoveLeft;
                } else if (sf::Keyboard::isKeyPressed(contr.value().MoveRight)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveRightSecondary)) {
                    hasMoved = true;
                    // if (lastEvent != ecs::Event(ecs::Event::EventType::MoveRight)) {
                        world.pushEvent(ecs::Event(ecs::Event::EventType::MoveRight));
                        lastEvent = ecs::Event::EventType::MoveRight;
                    // }
                    // contr.value().lastDirectionX = ecs::Event::EventType::MoveRight;
                }
                if (!hasMoved /*&& lastEvent != ecs::Event(ecs::Event::EventType::MoveStop)*/) {
                    world.pushEvent(ecs::Event(ecs::Event::EventType::MoveStop));
                    // std::cout << "stop" << std::endl;
                    lastEvent = ecs::Event::EventType::MoveStop;
                }

                if (shoot) {
                    if (sf::Keyboard::isKeyPressed(shoot.value().Shoot)
                        || sf::Keyboard::isKeyPressed(shoot.value().ShootSecondary))
                        world.pushEvent(ecs::Event(ecs::Event::EventType::Shoot));
                }
            }
        }
#endif
    };
} // namespace ecs::systems
