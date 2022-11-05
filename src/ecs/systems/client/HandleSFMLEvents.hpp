/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HandleSFMLEvents
*/

#pragma once

#include <functional>
#include "Window.hpp"
#include "World.hpp"

namespace ecs::systems
{
    std::function<World(void)> getTestWorld = []() {
        ecs::World world;

        Entity newEntity = world.registry.spawn_entity();

        world.registry.registerComponent<component::Position>();
        world.registry.registerComponent<component::Size>();
        world.registry.registerComponent<component::Drawable>();
        world.registry.registerComponent<component::Animated>();

        world.registry.addComponent<component::Position>(newEntity, {100, 100});
        world.registry.addComponent<component::Size>(newEntity, {100, 100});
        world.registry.addComponent<component::Drawable>(newEntity, {"players", {1, 35, 32, 16}});

        world.addSystem(ecs::systems::draw);

        return world;
    };
    /**
     * Used to manage Sfml events
     * Currently able to manage the following actions:
     * Close the window
     * KeyPressed, in this case, we check if the bind is known from sfml:
     * if yes, we had it on world's events' stack, nothing otherwise
     */
    std::function<void(World &)> handleSFMLEvents = [](World &world) {
        sf::Event event;
        auto &hitBoxes = world.registry.getComponents<component::Hitbox>();

        while (utils::Window::get().pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: utils::Window::get().close(); break;
                case sf::Event::KeyPressed: {
                    if (event.key.code == sf::Keyboard::Key::W)
                        ecs::WorldManager::setWaitingWorld(getTestWorld);
                } break;
                case sf::Event::KeyReleased: {
                    for (auto &hitBox : hitBoxes) {
                        if (hitBox == std::nullopt)
                            continue;
                        if (event.key.code == sf::Keyboard::H) {
                            hitBox->switchHitBox();
                            break;
                        }
                    }
                }
                default: break;
            }
        }
    };
} // namespace ecs::systems
