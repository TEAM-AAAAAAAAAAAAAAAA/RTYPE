/*
** EPITECH PROJECT, by hourcadettej on 11/11/22.
** rtype
** File description:
** rtype
*/

#pragma once
#include <string>

namespace ecs::component {
    struct Score {

        Score(size_t score = 0) : _score(score) {}

        inline void setScore(size_t score) {_score = score;}
        inline size_t getScore() const {return _score;}

      private:
        size_t _score;
    };
};
