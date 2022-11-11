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
        enum AIType { None, Battlecruiser, Dreadnought, Fighter, Frigate, Scout, Torpedo, NoodleMonster };

        /**
         * @brief All possible Patterns created
         *
         * @warning ALL MUST BE CREATED IN AttackAI.cpp
         */
        enum PatternType {
            Wait,
            WaitShort,
            WaitLong,
            ShootBullet,
            ShootEnergySphere,
            ShootEnergySphereFast,
            ShootLaser,
            ShootRocket,
            InvokeAllies,
            InvokeAnyone,
            SpawnAsteroids
        };

        size_t lastAttack;
        size_t lastAttackDelay;

        /**
         * @brief The AI structure where the pattern of the entity is defined
         */
        struct AI {
            /**
             * @brief The Pattern structure contains a std::functions and a reloadTime. Patterns are created in the CPP
             * file.
             *
             */
            struct Pattern {
                /**
                 * @brief Construct a new Pattern object
                 *
                 * @param reloadTime the time the entity will have to wait before using another pattern again after this
                 * one
                 * @param pattern the function to call when this pattern is selected to be used by the AI
                 */
                Pattern(short reloadTime, std::function<void(const std::size_t)> pattern)
                    : reloadTime(reloadTime), _function(pattern)
                {
                }

                /**
                 * @brief Run the pattern's function
                 *
                 * @param shooter which entity triggered the action
                 */
                void run(const std::size_t &shooter) const { _function(shooter); }

                short reloadTime;

                std::function<void(const std::size_t)> _function;
            };

            /**
             * @brief Construct a new AI object
             *
             * @param direction vector that takes pairs of chars
             * @param delay the delay between each step
             */
            AI(std::vector<PatternType> pattern) : _thisPatterns(pattern), currentAttack(0) {}

            /**
             * @brief AI copy constructor
             *
             * @param other another AI
             */
            AI(const AI &other) : currentAttack(other.currentAttack), _thisPatterns(other._thisPatterns) {}

            /**
             * @brief Get the Patterns of this AI
             *
             * @return const std::vector<PatternType>
             */
            inline const std::vector<PatternType> &getPatterns() const { return _thisPatterns; }

            static const std::unordered_map<PatternType, Pattern> patterns;

          private:
            short currentAttack;
            std::vector<PatternType> _thisPatterns;
        };

        /**
         * @brief The Action structure contains the prototypes of the functions used by patterns
         *
         */
        struct Action {
            static void waitAttack(const std::size_t shooter);
            static void shootBulletAttack(const std::size_t shooter);
            static void shootEnerySphereAttack(const std::size_t shooter);
            static void shootLaserAttack(const std::size_t shooter);
            static void shootRocketAttack(const std::size_t shooter);
            static void invokeAlliesAttack(const std::size_t shooter);
            static void spawnAsteroidsAttack(const std::size_t shooter);
            static void invokeAnyoneAttack(const std::size_t shooter);

          private:
            /**
             * @brief Utility function used by action functions to reduce code reusing
             */
            static void spawnNewBullet(component::EntityType::Types type, int posX, int posY, char dirX, char dirY,
                int sizeX, int sizeY, int velX, int velY, int dmg, ecs::component::Faction::Factions fac,
                int bulletHealth = 1);
        };

        /**
         * @brief AttackAI constructor
         *
         * @param type the AIType of the entity
         */
        AttackAI(const AIType &type = None) : _thisAI(findAI(type)), lastAttack(0), lastAttackDelay(0) {}

        /**
         * @brief Get a random attack from the AI
         */
        const AttackAI::AI::Pattern &getRandomAttack() const
        {
            int attack = _thisAI.getPatterns().at(std::rand() % _thisAI.getPatterns().size());
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
