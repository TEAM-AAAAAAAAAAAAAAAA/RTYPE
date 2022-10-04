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
    class Event {
      public:
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
