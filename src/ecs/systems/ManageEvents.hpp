/*
 * File: ManageEvents.hpp
 * Project: systems
 * File Created: Tuesday, 4th October 2022 10:17:07 pm
 * Author: Aurèle Nicolas (aurele.nicolas@epitech.eu)
 * -----
 * Last Modified: Tuesday, 4th October 2022 10:23:43 pm
 * Modified By: Aurèle Nicolas (aurele.nicolas@epitech.eu>)
 * -----
 * Copyright 2022 - 2022 Your Company, Your Company
 */

#pragma once

#include <functional>
#include "World.hpp"

namespace ecs::systems
{
    std::function<void(World &)> handleSFMLEvents = [](World &world) {
    }
}
