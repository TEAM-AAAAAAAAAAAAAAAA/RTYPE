/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** FollowEntity
*/

#pragma once

#include <cstddef>

namespace ecs::component
{
    struct FollowEntity {
        std::size_t entityId;
    };
} // namespace ecs::component
