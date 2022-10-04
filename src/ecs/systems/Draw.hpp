#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Drawable.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"

namespace ecs::systems
{
    std::function<void(World &)> draw = [](World &world) {
        auto const &positions = world.registry.getComponents<component::Position>();
        auto const &sizes = world.registry.getComponents<component::Size>();
        auto const &drawables = world.registry.getComponents<component::Drawable>();

        world.getWindow().clear();
        for (size_t i = 0; i < positions.size() && i < sizes.size() && i < drawables.size(); ++i) {
            auto const &pos = positions[i];
            auto const &size = sizes[i];
            auto const &draw = drawables[i];
            if (pos && size && draw) {
                sf::Texture texture;
                texture.loadFromFile(draw.value().Texture, sf::IntRect(0, 0, 16, 16));
                sf::Sprite sprite;
                sprite.setTexture(texture);
                world.getWindow().draw(sprite);
            }
        };
        world.getWindow().display();
    };
}
