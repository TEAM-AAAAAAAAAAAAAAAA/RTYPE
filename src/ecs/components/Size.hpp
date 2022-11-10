#pragma once

namespace ecs::component
{
    /// @brief Size component
    struct Size {
        int height;
        int width;
        /// @brief serialize the component
        /// @return the serialized component
        std::array<char, 4> serialize()
        {
            std::array<char, 4> pos;
            size_t tmp = 0;

            tmp = width >> 8;
            pos[0] = tmp;
            pos[1] = width & 0xff;
            tmp = height >> 8;
            pos[2] = tmp;
            pos[3] = height & 0xff;
            return pos;
        }
    };
} // namespace ecs::component
