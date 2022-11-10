#include <iostream>
#include "Constant.hpp"
#include "EnemyFactory.hpp"
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
#include "systems/server/Waves.hpp"

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
    world.addSystem(ecs::systems::waves);

    using AtkAI = ecs::component::AttackAI::AIType;
    using MovAI = ecs::component::MovementAI::AIType;
    using Fac = ecs::component::Faction;
    using EType = ecs::EnemyFactory::EnemyType;

    // ecs::EnemyFactory::spawnEnemy(world, EType::Dreadnought, 800, 400, Fac::Uranus, MovAI::Idle);
    // ecs::EnemyFactory::spawnEnemy(world, EType::Fighter, 400, 400, Fac::Janitor, MovAI::QuickLeftRight);
    // ecs::EnemyFactory::spawnEnemy(world, EType::Torpedo, 400, 400, Fac::Alien, MovAI::AntiClockwiseSmall);
    // ecs::EnemyFactory::spawnEnemy(world, EType::NoodleMonster, 1000, 400, Fac::None, MovAI::LongUpDown);
    // ecs::EnemyFactory::spawnEnemy(world, EType::Scout, 800, 800, Fac::Uranus, MovAI::Idle);

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
