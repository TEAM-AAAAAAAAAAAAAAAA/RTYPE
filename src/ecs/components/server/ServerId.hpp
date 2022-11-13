/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** ServerId
*/

#pragma once

namespace ecs::component
{
    struct ServerId {
        ServerId(char id) : id(id) {}
        char id;
    };
} // namespace ecs::component
