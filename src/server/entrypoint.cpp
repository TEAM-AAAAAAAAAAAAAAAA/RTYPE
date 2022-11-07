#include <iostream>
#include "Constant.hpp"
#include "Engine.hpp"
#include "Server.hpp"
#include "components/EntityAI.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/NetworkId.hpp"
#include "systems/Movement.hpp"
#include "systems/RunAI.hpp"
#include "systems/server/DeathUpdate.hpp"
#include "systems/server/HandleIncomingMessage.hpp"
#include "systems/server/PositionUpdate.hpp"
#include "systems/server/ProjectileCollision.hpp"

ecs::World getGameWorld()
{
    ecs::World world;

    ecs::Entity player = world.registry.spawn_entity();

    world.registry.registerComponent<ecs::component::Projectile>();
    world.registry.registerComponent<ecs::component::EntityAI>();
    world.registry.registerComponent<ecs::component::Direction>();
    world.registry.registerComponent<ecs::component::Weapon>();
    world.registry.registerComponent<ecs::component::Velocity>();
    world.registry.registerComponent<ecs::component::NetworkId>();
    world.registry.registerComponent<ecs::component::EntityType>();
    world.registry.registerComponent<ecs::component::Size>();
    world.registry.registerComponent<ecs::component::Faction>();
    world.registry.registerComponent<ecs::component::Position>();
    world.registry.registerComponent<ecs::component::Health>();

    world.addSystem(ecs::systems::movement);
    world.addSystem(ecs::systems::projectileCollision);
    world.addSystem(ecs::systems::HandleIncomingMessages);
    world.addSystem(ecs::systems::PositionUpdate);
    world.addSystem(ecs::systems::runAI);
    world.addSystem(ecs::systems::deathUpdate);

    using EntityAI = ecs::component::EntityAI;

    ecs::Entity enemy = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(enemy, {500, 500});
    world.registry.addComponent<ecs::component::Direction>(enemy, {0, 0});
    world.registry.addComponent<ecs::component::Size>(enemy, {32, 64});
    world.registry.addComponent<ecs::component::EntityAI>(enemy, {EntityAI::AIType::BasicUpDown});
    world.registry.addComponent<ecs::component::Health>(enemy, {100});
    world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Enemies});
    world.registry.addComponent<ecs::component::NetworkId>(enemy, {static_cast<size_t>(enemy)});
    world.registry.addComponent<ecs::component::EntityType>(enemy, {ecs::component::EntityType::Types::EnemyBase});
    world.registry.addComponent<ecs::component::Velocity>(enemy, {1, 1});

    return world;
}

int main()
{
    ecs::Engine engine;
    ecs::WorldManager::setWaitingWorld(getGameWorld);

    engine.run();
    return 0;
}
