/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** WorldManager
*/

#pragma once
#include <memory>
#include "World.hpp"

namespace ecs
{
    class Engine;

    class WorldManager {
      public:
        friend Engine;
        ~WorldManager() = default;

        static void setWorldSwitchReady(bool isReady = true) { getInstance()._worldSwitchReady = isReady; }

        /**
         * Used to get the currentWorld currently used by the ecs
         * @return The currently used world by the ecs
         */
        static ecs::World &getWorld() { return *getInstance()._currentWorld; }

        /**
         * Set the world given as parameter to release mode
         * @param world The world you want to set to release mode
         * @param worldSwitchReady Used to prevents of automatic world's switch
         */
        static void setWaitingWorld(std::function<World()> worldGen, bool worldSwitchReady = true)
        {
            if (getInstance()._waitingWorld)
                getInstance()._waitingWorld.release();
            getInstance()._waitingWorld = std::make_unique<ecs::World>(worldGen());
            getInstance()._worldSwitchReady = worldSwitchReady;
        }

        /**
         * Set the world given as parameter ready to switch for another one
         */
        static void setWorldSwitchReady() { getInstance()._worldSwitchReady = true; }

      private:
        bool _worldSwitchReady;
        std::unique_ptr<ecs::World> _currentWorld;
        std::unique_ptr<ecs::World> _waitingWorld;


        static WorldManager &getInstance();

        [[nodiscard]] static bool isWorldSwitchReady() { return getInstance()._worldSwitchReady; }

        static void switchWorlds()
        {
            if (getInstance()._waitingWorld)
                getInstance()._currentWorld.swap(getInstance()._waitingWorld);
            getInstance()._worldSwitchReady = false;
        }
    };
} // namespace ecs
