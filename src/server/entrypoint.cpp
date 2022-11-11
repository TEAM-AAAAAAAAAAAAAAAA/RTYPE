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
#include "systems/server/PeriodicPing.hpp"

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
    world.addSystem(ecs::systems::periodicPing);

    return world;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << argc << std::endl;
        std::cerr << "Usage: ./r-type_server [port]" << std::endl;
        return 1;
    }
    try {
        if (std::stoi(argv[1]) < 0) {
            std::cerr << "Port must be greater than 0" << std::endl;
            return 84;
        }
    } catch (std::exception &e) {
        std::cerr << "Port must be a number" << std::endl;
        return 84;
    }
    network::Server::start(std::stoi(argv[1]));
    std::srand(std::time(NULL));
    ecs::Engine engine;
    ecs::WorldManager::setWaitingWorld(getGameWorld);

    engine.run();
    return 0;
}
