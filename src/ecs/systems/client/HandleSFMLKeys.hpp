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
#include "Window.hpp"

namespace ecs::systems
{
    /**
     * Used to manage every action ordered by Sfml input by the user
     * Refer to the Controllable.hpp documentation to learn more about managed input
     */
    std::function<void(World &)> handleSFMLKeys = [](World &world) {
        if (!utils::Window::get().hasFocus())
            return;

#ifdef CLIENT_COMPILATION_MODE
        auto &controllables = world.registry.getComponents<component::Controllable>();
        auto const &shootables = world.registry.getComponents<component::Shootable>();

        for (size_t i = 0; i < controllables.size(); ++i) {
            auto &contr = controllables[i];

            if (contr) {
                bool hasMoved = false;
                static ecs::Event::EventType lastEventX;
                static ecs::Event::EventType lastEventY;
                static bool isStopped = false;

                if (sf::Keyboard::isKeyPressed(contr.value().MoveUp)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveUpSecondary)) {
                    hasMoved = true;
                    if (lastEventY != ecs::Event::EventType::MoveUp) {
                        world.pushEvent(ecs::Event(ecs::Event::EventType::MoveUp));
                        lastEventY = ecs::Event::EventType::MoveUp;
                        isStopped = false;
                    }
                } else if (sf::Keyboard::isKeyPressed(contr.value().MoveDown)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveDownSecondary)) {
                    hasMoved = true;
                    if (lastEventY != ecs::Event::EventType::MoveDown) {
                        world.pushEvent(ecs::Event(ecs::Event::EventType::MoveDown));
                        lastEventY = ecs::Event::EventType::MoveDown;
                        isStopped = false;
                    }
                }
                if (sf::Keyboard::isKeyPressed(contr.value().MoveLeft)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveLeftSecondary)) {
                    hasMoved = true;
                    if (lastEventX != ecs::Event::EventType::MoveLeft) {
                        world.pushEvent(ecs::Event(ecs::Event::EventType::MoveLeft));
                        lastEventX = ecs::Event::EventType::MoveLeft;
                        isStopped = false;
                    }
                } else if (sf::Keyboard::isKeyPressed(contr.value().MoveRight)
                    || sf::Keyboard::isKeyPressed(contr.value().MoveRightSecondary)) {
                    hasMoved = true;
                    if (lastEventX != ecs::Event::EventType::MoveRight) {
                        world.pushEvent(ecs::Event(ecs::Event::EventType::MoveRight));
                        lastEventX = ecs::Event::EventType::MoveRight;
                        isStopped = false;
                    }
                }
                if (!hasMoved) {
                    if (!isStopped)
                        world.pushEvent(ecs::Event(ecs::Event::EventType::MoveStop));
                    lastEventX = ecs::Event::EventType::MoveStop;
                    lastEventY = ecs::Event::EventType::MoveStop;
                    isStopped = true;
                }
                if (i < shootables.size()) {
                    auto const &shoot = shootables[i];
                    if (shoot) {
                        if (sf::Keyboard::isKeyPressed(shoot.value().Shoot)
                            || sf::Keyboard::isKeyPressed(shoot.value().ShootSecondary))
                            world.pushEvent(ecs::Event(ecs::Event::EventType::Shoot));
                    }
                }
            }
        }
#endif
    };
} // namespace ecs::systems
