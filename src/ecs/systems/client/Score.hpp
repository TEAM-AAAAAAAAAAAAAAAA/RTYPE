/*
** EPITECH PROJECT, 2022
** R-TYPEMIRROR
** File description:
** Score
*/

#pragma once

#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/client/Text.hpp"
#include <chrono>

static std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

namespace ecs::systems
{
    /**
     * Used to set the score of the player
     */
    std::function<void(World &)> score = [](World &world) {
        auto &texts = world.registry.getComponents<component::Text>();
        for (size_t i = 0; i < texts.size(); i++) {
            auto &text = texts[i];
            if (text) {
                if (text.value().content == "Score: ") {
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    auto const &elapsed = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 10);
                    text.value().setValue(elapsed);
                }
            }
        }
    };
} // namespace ecs::systems