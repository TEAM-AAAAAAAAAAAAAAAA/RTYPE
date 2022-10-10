/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** World
*/

#pragma once

#include <stack>
#include "Event.hpp"
#include "Registry.hpp"
#include "utils/Window.hpp"

namespace ecs
{
    /**
     * World class is used to contain all the components that are relevant to work together
     */
    class World {
      public:
        /**
         * Default constructor is deleted because you have to inform in which window you want to proceed
         */
        World() = delete;
        /**
         * Default constructor of World class
         * @param window The window in which the world have to proceed
         */
        explicit World(std::unique_ptr<utils::Window> &window) : _window(window) {}

        /**
         * Used to operate all the systems in the world
         */
        void runSystems()
        {
            for (auto &&i : _systems) {
                i(*this);
            }
        }

        /**
         * USed to add a new system into the world
         * @param system The system you want to add in the world in a constant manner
         */
        void addSystem(const std::function<void(World &)> &system) { _systems.push_back(system); }

        inline utils::Window &getWindow() { return *_window; }

        /**
         * Used to add a new event into the world
         * @param event The event you want to push in the world
         */
        void pushEvent(const ecs::Event event) { _events.push(event); }

        /**
         * Used to get the first event of the private stack _events
         * @return The first event of the private stack if it exists, ecs::Event::EventType::Null otherwise
         */
        const ecs::Event getEvent() const
        {
            if (_events.empty())
                return {ecs::Event::EventType::Null};
            return _events.top();
        }

        /**
         * Used to pop the first event of the private stack _events
         * @return The event you just popped out of the stack if it exists, ecs::Event::EventType::Null otherwise
         */
        const ecs::Event popEvent()
        {
            if (_events.empty())
                return {ecs::Event::EventType::Null};
            ecs::Event event = _events.top();
            _events.pop();
            return event;
        }

        /**
         * The registry of the world, refers to the Registry documentation to learn more about it
         */
        Registry registry;

      private:
        /**
         * The window used to display any information by the World class
         */
        std::unique_ptr<utils::Window> &_window;

        /**
         * Private system's vector of the World class
         */
        std::vector<std::function<void(World &)>> _systems;

        /**
         * Private events' stack of the World class
         */
        std::stack<ecs::Event> _events;
    };
} // namespace ecs
