#pragma once

#include "SFML/Graphics/Texture.hpp"

namespace ecs::component
{
    struct Drawable {
        Drawable(std::string texture) : Texture(texture) {}

        std::string Texture;
    };
} // namespace ecs::component
