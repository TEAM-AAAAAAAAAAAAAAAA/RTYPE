/*
 * File: Event.hpp
 * Project: ecs
 * File Created: Tuesday, 4th October 2022 7:31:30 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 7:34:03 pm
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
        Event(EventType e);

      private:
        EventType _e;
    };
} // namespace ecs
