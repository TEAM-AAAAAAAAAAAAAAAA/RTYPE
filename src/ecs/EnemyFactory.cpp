/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** EnemyFactory
*/

#include "EnemyFactory.hpp"
#include "World.hpp"
#include "WorldManager.hpp"
#include "components/Direction.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/MovementAI.hpp"
#include "components/NetworkId.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/server/AttackAI.hpp"

namespace ecs
{
    static void generateBattlecruiser(
        ecs::World &world, int posX, int posY, component::Faction::Factions fac, component::MovementAI::AIType movAI)
    {
        ecs::Entity enemy = world.registry.spawn_entity();

        world.registry.addComponent<ecs::component::Position>(enemy, {posX, posY});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {92, 76});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {2, 2});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {component::AttackAI::AIType::Battlecruiser});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {movAI});
        world.registry.addComponent<ecs::component::Health>(enemy, {1000});
        world.registry.addComponent<ecs::component::Faction>(enemy, {fac});
        switch (fac) {
            case component::Faction::Uranus:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::UranusBattlecruiser});
                break;
            case component::Faction::Janitor:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::JanitorBattlecruiser});
                break;
            case component::Faction::Alien:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::AlienBattlecruiser});
                break;
        }
    }

    static void generateDreadnought(
        ecs::World &world, int posX, int posY, component::Faction::Factions fac, component::MovementAI::AIType movAI)
    {
        ecs::Entity enemy = world.registry.spawn_entity();

        world.registry.addComponent<ecs::component::Position>(enemy, {posX, posY});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {152, 152});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {component::AttackAI::AIType::Dreadnought});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {movAI});
        world.registry.addComponent<ecs::component::Health>(enemy, {5000});
        world.registry.addComponent<ecs::component::Faction>(enemy, {fac});
        switch (fac) {
            case component::Faction::Uranus:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::UranusDreadnought});
                break;
            case component::Faction::Janitor:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::JanitorDreadnought});
                break;
            case component::Faction::Alien:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::AlienDreadnought});
                break;
        }
    }

    static void generateFighter(
        ecs::World &world, int posX, int posY, component::Faction::Factions fac, component::MovementAI::AIType movAI)
    {
        ecs::Entity enemy = world.registry.spawn_entity();

        world.registry.addComponent<ecs::component::Position>(enemy, {posX, posY});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {64, 64});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {5, 5});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {component::AttackAI::AIType::Fighter});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {movAI});
        world.registry.addComponent<ecs::component::Health>(enemy, {500});
        world.registry.addComponent<ecs::component::Faction>(enemy, {fac});
        switch (fac) {
            case component::Faction::Uranus:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::UranusFighter});
                break;
            case component::Faction::Janitor:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::JanitorFighter});
                break;
            case component::Faction::Alien:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::AlienFighter});
                break;
        }
    }

    static void generateFrigate(
        ecs::World &world, int posX, int posY, component::Faction::Factions fac, component::MovementAI::AIType movAI)
    {
        ecs::Entity enemy = world.registry.spawn_entity();

        world.registry.addComponent<ecs::component::Position>(enemy, {posX, posY});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {100, 100});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {5, 5});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {component::AttackAI::AIType::Frigate});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {movAI});
        world.registry.addComponent<ecs::component::Health>(enemy, {750});
        world.registry.addComponent<ecs::component::Faction>(enemy, {fac});
        switch (fac) {
            case component::Faction::Uranus:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::UranusFrigate});
                break;
            case component::Faction::Janitor:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::JanitorFrigate});
                break;
            case component::Faction::Alien:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::AlienFrigate});
                break;
        }
    }

    static void generateScout(
        ecs::World &world, int posX, int posY, component::Faction::Factions fac, component::MovementAI::AIType movAI)
    {
        ecs::Entity enemy = world.registry.spawn_entity();

        world.registry.addComponent<ecs::component::Position>(enemy, {posX, posY});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {48, 48});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {10, 10});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {component::AttackAI::AIType::Scout});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {movAI});
        world.registry.addComponent<ecs::component::Health>(enemy, {250});
        world.registry.addComponent<ecs::component::Faction>(enemy, {fac});
        switch (fac) {
            case component::Faction::Uranus:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::UranusScout});
                break;
            case component::Faction::Janitor:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::JanitorScout});
                break;
            case component::Faction::Alien:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::AlienScout});
                break;
        }
    }

    static void generateTorpedo(
        ecs::World &world, int posX, int posY, component::Faction::Factions fac, component::MovementAI::AIType movAI)
    {
        ecs::Entity enemy = world.registry.spawn_entity();

        world.registry.addComponent<ecs::component::Position>(enemy, {posX, posY});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {60, 60});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {5, 5});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {component::AttackAI::AIType::Torpedo});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {movAI});
        world.registry.addComponent<ecs::component::Health>(enemy, {500});
        world.registry.addComponent<ecs::component::Faction>(enemy, {fac});
        switch (fac) {
            case component::Faction::Uranus:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::UranusTorpedo});
                break;
            case component::Faction::Janitor:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::JanitorTorpedo});
                break;
            case component::Faction::Alien:
                world.registry.addComponent<ecs::component::EntityType>(
                    enemy, {ecs::component::EntityType::Types::AlienTorpedo});
                break;
        }
    }

    static void generateNoodleMonster(
        ecs::World &world, int posX, int posY, component::Faction::Factions fac, component::MovementAI::AIType movAI)
    {
        ecs::Entity enemy = world.registry.spawn_entity();

        world.registry.addComponent<ecs::component::Position>(enemy, {posX, posY});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {512, 512});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {5, 5});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {component::AttackAI::AIType::NoodleMonster});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {movAI});
        world.registry.addComponent<ecs::component::Health>(enemy, {25000});
        world.registry.addComponent<ecs::component::Faction>(enemy, {component::Faction::Factions::None});
        world.registry.addComponent<ecs::component::EntityType>(
            enemy, {ecs::component::EntityType::Types::NoodleMonster});
    }

    const std::unordered_map<EnemyFactory::EnemyType,
        std::function<void(ecs::World &, int, int, component::Faction::Factions, component::MovementAI::AIType)>>
        EnemyFactory::_typeGeneratorMap({{Battlecruiser, generateBattlecruiser}, {Dreadnought, generateDreadnought},
            {Fighter, generateFighter}, {Frigate, generateFrigate}, {Scout, generateScout}, {Torpedo, generateTorpedo},
            {NoodleMonster, generateNoodleMonster}});
} // namespace ecs
