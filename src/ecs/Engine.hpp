/*
 * File: Engine.hpp
 * Project: ecs
 * File Created: Tuesday, 4th October 2022 6:33:43 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Wednesday, 5th October 2022 2:05:52 pm
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
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "systems/Draw.hpp"
#include "systems/HandleSFMLEvents.hpp"
#include "systems/HandleSFMLMovements.hpp"
#include "systems/ManageClientEvents.hpp"
#include "systems/Movement.hpp"
#include "systems/PositionLogger.hpp"

namespace ecs
{
    /**
     * The Engine class manages the whole part of systems in ecs in a given world.
     * Systems are, most of the time, short function using components to realise some actions.
     * For example, to make an Entity move, we need a component Position and a component Velocity,
     * the system is the thing who update the position of the Entity according to the Velocity component
     * by adding velocity value to the x & y member of the component position of the Entity.
     */
    class Engine {
      public:
        /**
         * Constructor of Engine class, it takes care of register every component in the world's registry.
         * It also create a player and an enemy.
         * And finally it takes care of adding every systems related to the components in the initWorld.
         * @param wSizeWidth width size of the window in pixel, 800px as default
         * @param wSizeHeight height size of the window in pixel, 600 as default
         * @param wTitle window's title, "r-type" as default
         */
        explicit Engine(int wSizeWidth = 800, int wSizeHeight = 600, std::string wTitle = "r-type")
            : _worldSwitchReady(false)
        {
            _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(wSizeWidth, wSizeHeight), wTitle);
            _window.get()->setFramerateLimit(60);
            ecs::World initWorld(_window);
            ecs::Entity player = initWorld.registry.spawn_entity();
            initWorld.registry.addComponent<ecs::component::Position>(player, {10, 10});
            initWorld.registry.addComponent<ecs::component::Velocity>(player, {5, 5});
            initWorld.registry.addComponent<ecs::component::Size>(player, {2, 2});
            initWorld.registry.addComponent<ecs::component::Direction>(player, {0, 0});
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
            initWorld.addSystem(ecs::systems::handleSFMLMovements);
            initWorld.addSystem(ecs::systems::manageClientEvents);
            // initWorld.addSystem(ecs::systems::positionLogger);
            initWorld.addSystem(ecs::systems::draw);
            initWorld.addSystem(ecs::systems::movement);

            _currentWorld = std::make_unique<ecs::World>(initWorld);
        }

        /**
         * Used to get the currentWorld currently used by the ecs
         * @return The currently used world by the ecs
         */
        ecs::World &getWorld() { return *_currentWorld; }

        /**
         * Set the world given as parameter to release mode
         * @param world The world you want to set to release mode
         */
        void setWaitingWorld(ecs::World &world)
        {
            if (_waitingWorld)
                _waitingWorld.release();
            _waitingWorld = std::make_unique<ecs::World>(world);
        }

        /**
         * Set the world given as parameter ready to switch for another one
         */
        void setWorldSwitchReady() { _worldSwitchReady = true; }

        /**
         * Main loop of the current world
         * Actually run while the window is open
         */
        void run()
        {
            while (_window->isOpen()) {
                _currentWorld->runSystems();
                if (isWorldSwitchReady())
                    switchWorlds();
            }
        }

      private:
        /**
         * The window used to display every drawable component
         */
        std::unique_ptr<sf::RenderWindow> _window;
        std::unique_ptr<ecs::World> _currentWorld;
        std::unique_ptr<ecs::World> _waitingWorld;
        bool _worldSwitchReady;

        [[nodiscard]] bool isWorldSwitchReady() const { return _worldSwitchReady; }

        void switchWorlds()
        {
            if (_waitingWorld)
                _currentWorld.swap(_waitingWorld);
        }
    };
} // namespace ecs
