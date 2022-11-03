/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** EnemyAI
*/

#pragma once

#include <algorithm>
#include <vector>
#include <unordered_map>

namespace ecs::component
{
    /// @brief EnemyAI component
    struct EnemyAI {
      public:
        /**
         * @brief All possible AI created
         *
         * @warning ALL MUST BE CREATED IN EnemyAI.cpp
         */
        enum AIType { Idle, BasicUpDown };

        /**
         * @brief EnemyAI constructor
         *
         * @param type the AIType of the entity
         */
        EnemyAI(const AIType &type = Idle) : _thisAI(findAI(type)) {}

        /**
         * @brief get the next direction of the entity and cycles through the directions vector
         *
         * @return the next direction of the entity as a std::pair of chars
         */
        const std::pair<char, char> &getNextDirection()
        {
            if (_thisAI.currentIndex < _thisAI.direction.size()) {
                _thisAI.currentIndex++;
                return _thisAI.direction[_thisAI.currentIndex - 1];
            } else {
                _thisAI.currentIndex = 0;
                return _thisAI.direction[_thisAI.direction.size() - 1];
            }
        }

        /**
         * @brief Get the Delay between each AI steps
         *
         * @return const short& delay
         */
        inline const short &getDelay() const { return _thisAI.delay; }

      private:
        /**
         * @brief The AI structure where the pattern of the entity is defined
         */
        struct AI {
            /**
             * @brief Construct a new AI object
             *
             * @param direction vector that takes pairs of chars
             * @param delay the delay between each step
             */
            AI(std::vector<std::pair<char, char>> direction, short delay)
                : direction(direction), delay(delay), currentIndex(0)
            {
            }

            /**
             * @brief AI copy constructor
             *
             * @param other another AI
             */
            AI(const AI &other) : currentIndex(other.currentIndex), delay(other.delay), direction(other.direction) {}

            std::vector<std::pair<char, char>> direction;
            int currentIndex;
            short delay;
        };

        AI _thisAI;

        /**
         * @brief Find an AI by it's AIType
         *
         * @param type
         * @return the AI
         * @warning may throw if used badly or if all AIs are not defined in EnemyAI.cpp
         */
        inline const AI &findAI(const AIType &type) { return _aiVector.at(type); }

        static const std::unordered_map<AIType, AI> _aiVector;
    };
} // namespace ecs::component
