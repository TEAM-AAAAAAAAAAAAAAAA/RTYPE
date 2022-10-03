#pragma once

#include "../ecs/Registry.hpp"
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
    };
} // namespace ecs
