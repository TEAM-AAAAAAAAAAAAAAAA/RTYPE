/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Engine
*/

#pragma once

#include <filesystem>
#include <memory>
#include "AssetManager.hpp"
#include "Engine.hpp"
#include "Registry.hpp"
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
#ifndef CLIENT_COMPILATION_MODE
    #include "../server/Server.hpp"
extern network::Server SERVER;
#endif

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
        explicit Engine() : _worldSwitchReady(false)
        {
            _window = std::make_unique<utils::Window>();
            ecs::World initWorld(_window);
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
         * @param worldSwitchReady Used to prevents of automatic world's switch
         */
        void setWaitingWorld(const ecs::World &world, bool worldSwitchReady = true)
        {
            if (_waitingWorld)
                _waitingWorld.release();
            _waitingWorld = std::make_unique<ecs::World>(world);
            _worldSwitchReady = worldSwitchReady;
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

        inline std::unique_ptr<utils::Window> &getWindow() { return _window; }

      private:
        /**
         * The window used to display every drawable component
         */
        std::unique_ptr<utils::Window> _window;
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
