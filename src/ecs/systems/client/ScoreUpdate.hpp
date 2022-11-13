/*
** EPITECH PROJECT, 2022
** R-TYPEMIRROR
** File description:
** Score
*/

#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include "World.hpp"
#include "components/Score.hpp"
#include "components/client/Text.hpp"

namespace ecs::systems
{
    /**
     * Used to set the score of the player
     */
    std::function<void(World &)> scoreUpdate = [](World &world) {
        auto &texts = world.registry.getComponents<component::Text>();
        auto &scores = world.registry.getComponents<component::Score>();

        static std::chrono::high_resolution_clock::time_point begin = utils::constant::chrono::now();
        for (size_t i = 0; i < texts.size() && i < scores.size(); i++) {
            auto &text = texts[i];
            auto &score = scores[i];

            if (text && score) {
                if (text.value().getContent(0) == "Score: ") {
                    std::chrono::high_resolution_clock::time_point end = utils::constant::chrono::now();
                    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 10;
                    auto elapsed = std::to_string(time);

                    text->setContent(1, elapsed);
                    score->setScore(time);
                }
            }
        }
    };
} // namespace ecs::systems