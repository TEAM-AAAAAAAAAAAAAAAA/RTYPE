/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** AttackAI
*/

#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include "World.hpp"
#include "components/EntityType.hpp"
#include "components/Faction.hpp"
#include <unordered_map>

namespace ecs::component
{
    /// @brief AttackAI component
    struct AttackAI {
      public:
        /**
         * @brief All possible AI created
         *
         * @warning ALL MUST BE CREATED IN AttackAI.cpp
         */
        enum AIType { Scout, Fighter };

        /**
         * @brief All possible Patterns created
         *
         * @warning ALL MUST BE CREATED IN AttackAI.cpp
         */
        enum PatternType { ShootBullet, ShootEnergySphere };

        size_t lastAttack;
        size_t lastAttackDelay;

        /**
         * @brief The AI structure where the pattern of the entity is defined
         */
        struct AI {
            struct Pattern {
                Pattern(short reloadTime, std::function<void(const std::size_t)> pattern)
                    : reloadTime(reloadTime), _function(pattern)
                {
                }

                void run(const std::size_t &i) const { _function(i); }

                short reloadTime;

              private:
                std::function<void(const std::size_t)> _function;
            };

            /**
             * @brief Construct a new AI object
             *
             * @param direction vector that takes pairs of chars
             * @param delay the delay between each step
             */
            AI(std::vector<PatternType> patterns) : currentAttack(0)
            {
                for (auto &&p : patterns) {
                    _thisPatterns.push_back(patterns.at(p));
                }
            }

            /**
             * @brief AI copy constructor
             *
             * @param other another AI
             */
            AI(const AI &other) : currentAttack(other.currentAttack), _thisPatterns(other._thisPatterns) {}

            inline const std::vector<PatternType> getPatterns() const { return _thisPatterns; }

            static const std::unordered_map<PatternType, Pattern> patterns;

          private:
            short currentAttack;
            std::vector<PatternType> _thisPatterns;
        };

        struct Action {
            static void shootBulletAttack(const std::size_t shooter);
            static void shootEnerySphereAttack(const std::size_t shooter);

          private:
            static void spawnNewBullet(component::EntityType::Types type, int posX, int posY, char dirX, char dirY,
                int sizeX, int sizeY, int velX, int velY, int dmg, ecs::component::Faction::Factions fac);
        };

        /**
         * @brief AttackAI constructor
         *
         * @param type the AIType of the entity
         */
        AttackAI(const AIType &type = Scout) : _thisAI(findAI(type)), lastAttack(0), lastAttackDelay(0) {}

        const AttackAI::AI::Pattern &getRandomAttack() const
        {
            int attack = std::rand() % _thisAI.getPatterns().size();
            return AI::patterns.at(static_cast<PatternType>(attack));
        }

      private:
        AI _thisAI;

        /**
         * @brief Find an AI by it's AIType
         *
         * @param type
         * @return the AI
         * @warning may throw if used badly or if all AIs are not defined in AttackAI.cpp
         */
        inline const AI &findAI(const AIType &type) { return _aiVector.at(type); }

        static const std::unordered_map<AIType, AI> _aiVector;
    };
} // namespace ecs::component
