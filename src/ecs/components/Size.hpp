#pragma once

namespace ecs::component
{
    struct Size {
        int height;
        int width;
        std::array<char, 2> serialize()
        {
            std::array<char, 2> pos;

            pos[0] = width & 0xff;
            pos[1] = height & 0xff;
            return pos;
        }
    };
} // namespace ecs::component
