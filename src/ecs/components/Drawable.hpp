#pragma once

#include "SFML/Graphics/Texture.hpp"

namespace ecs::component
{
    struct Drawable {
        Drawable(sf::Texture texture) : Texture(texture) {}

        sf::Texture Texture;
    };
} // namespace ecs::component
