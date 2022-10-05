/*
 * File: Event.hpp
 * Project: ecs
 * File Created: Tuesday, 4th October 2022 7:31:30 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 11:08:42 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
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

            bool operator==(const Event other) const
            {
                if (_e == other._e)
                    return true;
                return false;
            }

            bool operator==(const Event::EventType type) const
            {
                if (_e == type)
                    return true;
                return false;
            }

        private:
            const EventType _e;
    };
} // namespace ecs
