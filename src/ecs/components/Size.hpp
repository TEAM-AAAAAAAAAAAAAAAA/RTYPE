#pragma once

namespace ecs::component
{
    /// @brief Size component
    struct Size {
        int height;
        int width;
        /// @brief serialize the component
        /// @return the serialized component
        std::array<char, 2> serialize()
        {
            std::array<char, 2> pos;

            pos[0] = width & 0xff;
            pos[1] = height & 0xff;
            return pos;
        }
    };
} // namespace ecs::component
