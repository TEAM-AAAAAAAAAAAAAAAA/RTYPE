/*
 * File: World.hpp
 * Project: ecs
 * File Created: Tuesday, 4th October 2022 6:33:43 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 11:02:57 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <stack>
#include "Event.hpp"
#include "Registry.hpp"
#include "SFML/Graphics.hpp"

namespace ecs
{
    class World {
      public:
        World(std::unique_ptr<sf::RenderWindow> &window) : _window(window) {}

        void runSystems()
        {
            for (auto &&i : _systems) {
                i(*this);
            }
        }

        void addSystem(std::function<void(World &)> system) { _systems.push_back(system); }

        sf::RenderWindow &getWindow() { return *_window; }

        void pushEvent(ecs::Event event) { _events.push(event); }

        const ecs::Event getEvent()
        {
            if (_events.size() == 0)
                return ecs::Event(ecs::Event::EventType::Unknown);
            return _events.top();
        }

        const ecs::Event popEvent()
        {
            if (_events.size() == 0)
                return ecs::Event(ecs::Event::EventType::Unknown);
            ecs::Event event = _events.top();
            _events.pop();
            return event;
        }

        // class Entity {
        //   public:
        //     Entity(ecs::Registry &r, ecs::Entity &e) : _e(e) { _registry = std::make_unique<ecs::Registry>(r); }

        //   private:
        //     std::unique_ptr<ecs::Registry> _registry;
        //     ecs::Entity _e;
        // };

        Registry registry;

      private:
        std::unique_ptr<sf::RenderWindow> &_window;
        std::vector<std::function<void(World &)>> _systems;
        std::stack<ecs::Event> _events;
    };
} // namespace ecs
