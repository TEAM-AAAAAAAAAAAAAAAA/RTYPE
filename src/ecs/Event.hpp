/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Event
*/

#pragma once

namespace ecs
{
    /**
     * Event class is used to manage every events gave by the user
     * The Event class make the link between the user and the back-end
     */
    class Event {
      public:
        /**
         * List every type of event currently managed
         */
        enum EventType {
            Null,
            Unknown,
            Quit,
            Move,
            MoveUp,
            MoveLeft,
            MoveDown,
            MoveRight,
            Shoot,
            UIUp,
            UILeft,
            UIDown,
            UIRight,
            UIEnter,
        };
        /**
         * Default constructor is deleted because you have to inform the event you want to treat
         */
        Event() = delete;

        /**
         * Constructor of Event class
         * @param e The Event you want to treat
         */
        Event(EventType e) : _e(e) {}

        inline bool operator==(const Event other) const
        {
            if (_e == other._e)
                return true;
            return false;
        }

        inline bool operator==(const Event::EventType type) const
        {
            if (_e == type)
                return true;
            return false;
        }

        inline bool operator!=(const Event other) const { return _e != other._e; };

        inline bool operator!=(const Event::EventType type) const { return _e != type; };

        inline char serialize() const { return _e; }

      private:
        const EventType _e;
    };
} // namespace ecs
