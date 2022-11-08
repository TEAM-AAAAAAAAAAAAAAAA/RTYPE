/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** MovementAI
*/

#pragma once

#include <algorithm>
#include <vector>
#include <unordered_map>

namespace ecs::component
{
    /// @brief MovementAI component
    struct MovementAI {
      public:
        /**
         * @brief All possible AI created
         *
         * @warning ALL MUST BE CREATED IN MovementAI.cpp
         */
        enum AIType { Idle, BasicUpDown, ClockwiseSmall, ClockwiseBig };

        /**
         * @brief MovementAI constructor
         *
         * @param type the AIType of the entity
         */
        MovementAI(const AIType &type = Idle) : _thisAI(findAI(type)) {}

        /**
         * @brief get the next direction of the entity and cycles through the directions vector
         *
         * @return the next direction of the entity as a std::pair of chars
         */
        inline const std::pair<char, char> &getNextDirection()
        {
            if (_thisAI.currentIndex < _thisAI.direction.size() - 1) {
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
         * @return the delay in seconds
         */
        inline const short &getDelay() const { return _thisAI.delay; }

        /**
         * @brief Get the last time the AI entity has moved
         *
         * @return the last time the AI has moved
         */
        inline const std::size_t &getLastMovement() const { return _thisAI.lastMovement; }

        /**
         * @brief Set the last time the AI entity has moved
         * 
         * @param lastMovement the last time the AI has moved
         */
        inline void setLastMovement(const std::size_t &lastMovement) { _thisAI.lastMovement = lastMovement; }

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
            std::size_t lastMovement;
        };

        AI _thisAI;

        /**
         * @brief Find an AI by it's AIType
         *
         * @param type
         * @return the AI
         * @warning may throw if used badly or if all AIs are not defined in MovementAI.cpp
         */
        inline const AI &findAI(const AIType &type) { return _aiVector.at(type); }

        static const std::unordered_map<AIType, AI> _aiVector;
    };
} // namespace ecs::component
