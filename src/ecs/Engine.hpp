/*
 * File: Engine.hpp
 * Project: ecs
 * File Created: Tuesday, 4th October 2022 6:33:43 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Wednesday, 5th October 2022 12:40:43 am
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <memory>
#include "Engine.hpp"
#include "Registry.hpp"
#include "SFML/Graphics.hpp"
#include "World.hpp"
#include "components/Controllable.hpp"
#include "components/Drawable.hpp"
#include "components/EnemyAI.hpp"
#include "components/Position.hpp"
#include "components/Shootable.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "systems/Draw.hpp"
#include "systems/HandleSFMLEvents.hpp"
#include "systems/HandleSFMLKeys.hpp"
#include "systems/ManageClientEvents.hpp"
#include "systems/Movement.hpp"
#include "systems/PositionLogger.hpp"

namespace ecs
{
    class Engine {
      public:
        Engine(int wSizeX = 800, int wSizeY = 600, std::string wTitle = "r-type") : _worldSwitchReady(false)
        {
            _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(wSizeX, wSizeY), wTitle);
            _window.get()->setFramerateLimit(60);
            ecs::World initWorld(_window);
            ecs::Entity player = initWorld.registry.spawn_entity();
            initWorld.registry.addComponent<ecs::component::Position>(player, {10, 10});
            initWorld.registry.addComponent<ecs::component::Velocity>(player, {5, 5});
            initWorld.registry.addComponent<ecs::component::Size>(player, {2, 2});
            initWorld.registry.addComponent<ecs::component::Direction>(player, {0, 0});
            initWorld.registry.addComponent<ecs::component::Shootable>(player, {sf::Keyboard::Space});
            initWorld.registry.addComponent<ecs::component::Drawable>(
                player, {"src/demo/assets/textures/players.gif", {1, 1, 32, 16}});
            initWorld.registry.addComponent<ecs::component::Controllable>(
                player, {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D});

            ecs::Entity enemy = initWorld.registry.spawn_entity();
            initWorld.registry.addComponent<ecs::component::Position>(enemy, {500, 500});
            initWorld.registry.addComponent<ecs::component::Size>(enemy, {5, 5});
            initWorld.registry.addComponent<ecs::component::Drawable>(
                enemy, {"src/demo/assets/textures/players.gif", {1, 18, 32, 16}});
            initWorld.registry.addComponent<ecs::component::EnemyAI>(enemy, {});

            initWorld.addSystem(ecs::systems::handleSFMLEvents);
            initWorld.addSystem(ecs::systems::handleSFMLKeys);
            initWorld.addSystem(ecs::systems::manageClientEvents);
            // initWorld.addSystem(ecs::systems::positionLogger);
            initWorld.addSystem(ecs::systems::draw);
            initWorld.addSystem(ecs::systems::movement);

            _currentWorld = std::make_unique<ecs::World>(initWorld);
        }

        ecs::World &getWorld() { return *_currentWorld; }

        void setWaitingWorld(ecs::World &world)
        {
            if (_waitingWorld)
                _waitingWorld.release();
            _waitingWorld = std::make_unique<ecs::World>(world);
        }

        void setWorldSwitchReady() { _worldSwitchReady = true; }

        void run()
        {
            while (_window.get()->isOpen()) {
                _currentWorld.get()->runSystems();
                if (isWorldSwitchReady())
                    switchWorlds();
            }
        }

        // Entity createEntity() { return _currentWorld.get()->registry.spawn_entity(); }

      private:
        std::unique_ptr<sf::RenderWindow> _window;
        std::unique_ptr<ecs::World> _currentWorld;
        std::unique_ptr<ecs::World> _waitingWorld;
        bool _worldSwitchReady;

        bool isWorldSwitchReady() { return _worldSwitchReady; }

        void switchWorlds()
        {
            if (_waitingWorld)
                _currentWorld.swap(_waitingWorld);
        }
    };
} // namespace ecs
