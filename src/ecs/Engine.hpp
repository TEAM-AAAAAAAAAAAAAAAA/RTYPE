/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Engine
*/

#pragma once

#include <filesystem>
#include <functional>
#include <memory>
#include "Engine.hpp"
#include "Registry.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "WorldManager.hpp"

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
        explicit Engine()
        {
            ecs::WorldManager::setWorldSwitchReady(false);
            ecs::World initWorld;
            ecs::WorldManager::_Instance._currentWorld = std::make_unique<ecs::World>(initWorld);
        }

        /**
         * Main loop of the current world
         * Actually run while the window is open
         */
        void run()
        {
            while (utils::Window::isOpen()) {
                ecs::WorldManager::getWorld().runSystems();
                if (ecs::WorldManager::isWorldSwitchReady())
                    ecs::WorldManager::switchWorlds();
            }
        }
    };
} // namespace ecs
