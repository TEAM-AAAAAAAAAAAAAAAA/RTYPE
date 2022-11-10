#include <memory>
#include "World.hpp"

namespace ecs
{
    class Engine;

    class WorldManager {
      public:
        friend Engine;
        ~WorldManager() = default;

        static void setWorldSwitchReady(bool isReady = true) { _Instance._worldSwitchReady = isReady; }

        /**
         * Used to get the currentWorld currently used by the ecs
         * @return The currently used world by the ecs
         */
        static ecs::World &getWorld() { return *_Instance._currentWorld; }

        /**
         * Set the world given as parameter to release mode
         * @param world The world you want to set to release mode
         * @param worldSwitchReady Used to prevents of automatic world's switch
         */
        static void setWaitingWorld(std::function<World()> worldGen, bool worldSwitchReady = true)
        {
            if (_Instance._waitingWorld)
                _Instance._waitingWorld.release();
            _Instance._waitingWorld = std::make_unique<ecs::World>(worldGen());
            _Instance._worldSwitchReady = worldSwitchReady;
        }

        /**
         * Set the world given as parameter ready to switch for another one
         */
        static void setWorldSwitchReady() { _Instance._worldSwitchReady = true; }

      private:
        bool _worldSwitchReady;
        std::unique_ptr<ecs::World> _currentWorld;
        std::unique_ptr<ecs::World> _waitingWorld;

        static WorldManager _Instance;

        [[nodiscard]] static bool isWorldSwitchReady() { return _Instance._worldSwitchReady; }

        static void switchWorlds()
        {
            if (_Instance._waitingWorld)
                _Instance._currentWorld.swap(_Instance._waitingWorld);
            _Instance._worldSwitchReady = false;
        }
    };
} // namespace ecs
