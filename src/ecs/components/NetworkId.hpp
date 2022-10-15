/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#pragma once
#include <array>
#include <cstddef>

namespace ecs::component
{
    /// @brief NetworkId component related to the entity sent to the client
    struct NetworkId {
        NetworkId() : id(_last_id + 1) { _last_id++; }

        NetworkId(size_t id) : id(id) {}

        size_t id;
        /// @brief Serialize the component
        /// @return The serialized component
        std::array<char, 2> serialize()
        {
            std::array<char, 2> arr;
            size_t tmp = 0;

            tmp = id >> 8;
            arr[0] = tmp;
            arr[1] = id & 0xff;
            return arr;
        }

      private:
        static size_t _last_id;
    };
} // namespace ecs::component
