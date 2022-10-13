#include <iostream>
#include "Engine.hpp"
#include "components/Network.hpp"
// #include "components/Faction.hpp"
#include "components/Health.hpp"
// #include "systems/ProjectileCollision.hpp"

ecs::World getGameWorld(ecs::Engine &engine)
{
    ecs::World world(engine.getWindow());

    ecs::Entity player = world.registry.spawn_entity();
    ecs::Entity network = world.registry.spawn_entity();

    world.registry.registerComponent<ecs::component::Projectile>();
    world.registry.addComponent<ecs::component::Network>(network, {8000});

    world.registry.addComponent<ecs::component::Position>(player, {10, 10});
    world.registry.addComponent<ecs::component::Velocity>(player, {5, 5});
    world.registry.addComponent<ecs::component::Size>(player, {32, 64});
    world.registry.addComponent<ecs::component::Direction>(player, {1, 0});
    world.registry.addComponent<ecs::component::Weapon>(player, {100, 10});
    world.registry.addComponent<ecs::component::Health>(player, {100});
    // world.registry.addComponent<ecs::component::Faction>(player, {ecs::component::Faction::Factions::Players});
    // world.addSystem(ecs::systems::positionLogger);
    world.addSystem(ecs::systems::movement);
    // world.addSystem(ecs::systems::projectileCollision);

    ecs::Entity enemy = world.registry.spawn_entity();
    world.registry.addComponent<ecs::component::Position>(enemy, {500, 500});
    world.registry.addComponent<ecs::component::Size>(enemy, {64, 128});
    world.registry.addComponent<ecs::component::EnemyAI>(enemy, {});
    world.registry.addComponent<ecs::component::Health>(enemy, {100});
    // world.registry.addComponent<ecs::component::Faction>(enemy, {ecs::component::Faction::Factions::Enemies});

    return world;
}

int main()
{
    ecs::Engine engine;
    engine.setWaitingWorld(getGameWorld(engine));

    engine.run();
    return 0;
}
