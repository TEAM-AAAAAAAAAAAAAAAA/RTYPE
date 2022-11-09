#include <iostream>
#include "Constant.hpp"
#include "Engine.hpp"
#include "Server.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/MovementAI.hpp"
#include "components/NetworkId.hpp"
#include "systems/Movement.hpp"
#include "systems/RunMovementAI.hpp"
#include "systems/server/DeathUpdate.hpp"
#include "systems/server/HandleIncomingMessage.hpp"
#include "systems/server/PositionUpdate.hpp"
#include "systems/server/ProjectileCollision.hpp"
#include "systems/server/RunAttackAI.hpp"

ecs::World getGameWorld()
{
    ecs::World world;

    ecs::Entity player = world.registry.spawn_entity();

    world.registry.registerComponent<ecs::component::Projectile>();
    world.registry.registerComponent<ecs::component::MovementAI>();
    world.registry.registerComponent<ecs::component::Direction>();
    world.registry.registerComponent<ecs::component::Weapon>();
    world.registry.registerComponent<ecs::component::Velocity>();
    world.registry.registerComponent<ecs::component::NetworkId>();
    world.registry.registerComponent<ecs::component::EntityType>();
    world.registry.registerComponent<ecs::component::Size>();
    world.registry.registerComponent<ecs::component::Faction>();
    world.registry.registerComponent<ecs::component::Position>();
    world.registry.registerComponent<ecs::component::Health>();
    world.registry.registerComponent<ecs::component::AttackAI>();

    world.addSystem(ecs::systems::movement);
    world.addSystem(ecs::systems::projectileCollision);
    world.addSystem(ecs::systems::HandleIncomingMessages);
    world.addSystem(ecs::systems::PositionUpdate);
    world.addSystem(ecs::systems::runMovementAI);
    world.addSystem(ecs::systems::runAttackAI);
    world.addSystem(ecs::systems::deathUpdate);

    using MovementAI = ecs::component::MovementAI;
    using AttackAI = ecs::component::AttackAI;

    {
        ecs::Entity enemy = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::Position>(enemy, {500, 500});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {48, 48});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {MovementAI::AIType::Idle});
        world.registry.addComponent<ecs::component::Health>(enemy, {100});
        world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Uranus});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::EntityType>(enemy, {ecs::component::EntityType::Types::UranusFighter});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {2, 2});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {AttackAI::AIType::Fighter});
    }

    {
        ecs::Entity enemy = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::Position>(enemy, {600, 600});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {48, 48});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {MovementAI::AIType::QuickUpDown});
        world.registry.addComponent<ecs::component::Health>(enemy, {100});
        world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Uranus});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::EntityType>(enemy, {ecs::component::EntityType::Types::UranusFighter});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {2, 2});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {AttackAI::AIType::Fighter});
    }

    {
        ecs::Entity enemy = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::Position>(enemy, {600, 600});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {48, 48});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {MovementAI::AIType::QuickLeftRight});
        world.registry.addComponent<ecs::component::Health>(enemy, {100});
        world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Uranus});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::EntityType>(enemy, {ecs::component::EntityType::Types::UranusFighter});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {2, 2});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {AttackAI::AIType::Fighter});
    }

    {
        ecs::Entity enemy = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::Position>(enemy, {650, 650});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {32, 32});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {MovementAI::AIType::LongUpDown});
        world.registry.addComponent<ecs::component::Health>(enemy, {25});
        world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Uranus});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::EntityType>(enemy, {ecs::component::EntityType::Types::UranusScout});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {5, 5});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {AttackAI::AIType::Scout});
    }

    {
        ecs::Entity enemy = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::Position>(enemy, {650, 650});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {32, 32});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {MovementAI::AIType::LongLeftRight});
        world.registry.addComponent<ecs::component::Health>(enemy, {25});
        world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Uranus});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::EntityType>(enemy, {ecs::component::EntityType::Types::UranusScout});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {5, 5});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {AttackAI::AIType::Scout});
    }

    {
        ecs::Entity enemy = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::Position>(enemy, {400, 400});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {32, 32});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {MovementAI::AIType::ClockwiseSmall});
        world.registry.addComponent<ecs::component::Health>(enemy, {25});
        world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Uranus});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::EntityType>(enemy, {ecs::component::EntityType::Types::UranusScout});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {5, 5});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {AttackAI::AIType::Scout});
    }

    {
        ecs::Entity enemy = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::Position>(enemy, {400, 400});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {32, 32});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {MovementAI::AIType::ClockwiseBig});
        world.registry.addComponent<ecs::component::Health>(enemy, {25});
        world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Uranus});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::EntityType>(enemy, {ecs::component::EntityType::Types::UranusScout});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {5, 5});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {AttackAI::AIType::Scout});
    }

    {
        ecs::Entity enemy = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::Position>(enemy, {700, 700});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {32, 32});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {MovementAI::AIType::AntiClockwiseSmall});
        world.registry.addComponent<ecs::component::Health>(enemy, {25});
        world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Uranus});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::EntityType>(enemy, {ecs::component::EntityType::Types::UranusScout});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {5, 5});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {AttackAI::AIType::Scout});
    }

    {
        ecs::Entity enemy = world.registry.spawn_entity();
        world.registry.addComponent<ecs::component::Position>(enemy, {700, 700});
        world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
        world.registry.addComponent<ecs::component::Size>(enemy, {48, 48});
        world.registry.addComponent<ecs::component::MovementAI>(enemy, {MovementAI::AIType::AntiClockwiseBig});
        world.registry.addComponent<ecs::component::Health>(enemy, {100});
        world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Uranus});
        world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
        world.registry.addComponent<ecs::component::EntityType>(enemy, {ecs::component::EntityType::Types::UranusFighter});
        world.registry.addComponent<ecs::component::Velocity>(enemy, {2, 2});
        world.registry.addComponent<ecs::component::AttackAI>(enemy, {AttackAI::AIType::Fighter});
    }

    return world;
}

int main()
{
    network::Server::start(8000);
    std::srand(std::time(NULL));
    ecs::Engine engine;
    ecs::WorldManager::setWaitingWorld(getGameWorld);

    engine.run();
    return 0;
}
