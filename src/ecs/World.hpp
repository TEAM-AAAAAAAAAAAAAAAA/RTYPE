/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** World
*/

#pragma once

#include <queue>
#include "Event.hpp"
#include "Registry.hpp"

namespace ecs
{
    /**
     * World class is used to contain all the components that are relevant to work together
     */
    class World {
      public:
        /**
         * Default constructor
         */
        World() {};

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
            return _events.front();
        }

        /**
         * Used to pop the first event of the private stack _events
         * @return The event you just popped out of the stack if it exists, ecs::Event::EventType::Null otherwise
         */
        const ecs::Event popEvent()
        {
            if (_events.empty())
                return {ecs::Event::EventType::Null};
            ecs::Event event = _events.front();
            _events.pop();
            return event;
        }

        /**
         * The registry of the world, refers to the Registry documentation to learn more about it
         */
        Registry registry;

      private:
        /**
         * Private system's vector of the World class
         */
        std::vector<std::function<void(World &)>> _systems;

        /**
         * Private events' stack of the World class
         */
        std::queue<ecs::Event> _events;
    };
} // namespace ecs
