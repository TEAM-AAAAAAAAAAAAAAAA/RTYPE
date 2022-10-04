#pragma once

#include <memory>
#include "Engine.hpp"
#include "Registry.hpp"
#include "World.hpp"
#include "components/Controllable.hpp"
#include "components/Drawable.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "systems/Draw.hpp"
#include "systems/Movement.hpp"
#include "systems/PositionLogger.hpp"
#include "SFML/Graphics.hpp"

namespace ecs
{
    class Engine {
      public:
        Engine(int wSizeX = 800, int wSizeY = 600, std::string wTitle = "r-type")
        {
            _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(wSizeX, wSizeY), wTitle);
            ecs::World initWorld(_window);
            ecs::Entity player = initWorld.registry.spawn_entity();
            initWorld.registry.addComponent<ecs::component::Position>(player, {10, 10});
            initWorld.registry.addComponent<ecs::component::Velocity>(player, {1, 1});
            initWorld.registry.addComponent<ecs::component::Size>(player, {10, 10});
            initWorld.registry.addComponent<ecs::component::Drawable>(player, {""});
            initWorld.registry.addComponent<ecs::component::Controllable>(
                player, {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D});

            ecs::Entity enemy = initWorld.registry.spawn_entity();
            initWorld.registry.addComponent<ecs::component::Position>(enemy, {50, 50});
            initWorld.registry.addComponent<ecs::component::Size>(enemy, {10, 10});
            initWorld.registry.addComponent<ecs::component::Drawable>(enemy, {""});

            initWorld.addSystem(ecs::systems::positionLogger);
            initWorld.addSystem(ecs::systems::draw);

            _currentWorld = std::make_unique<ecs::World>(initWorld);
        }

        ecs::World &getWorld() { return *_currentWorld; }

        void setWaitingWorld(ecs::World &world)
        {
            if (_waitingWorld)
                _waitingWorld.release();
            _waitingWorld = std::make_unique<ecs::World>(world);
        }

        void switchWorlds()
        {
            if (_waitingWorld)
                _currentWorld.swap(_waitingWorld);
        }

        void run()
        {
            while (true) {
                _currentWorld.get()->runSystems();
            }
        }

        // Entity createEntity() { return _currentWorld.get()->registry.spawn_entity(); }

      private:
        std::unique_ptr<sf::RenderWindow> _window;
        std::unique_ptr<ecs::World> _currentWorld;
        std::unique_ptr<ecs::World> _waitingWorld;
    };
} // namespace ecs
