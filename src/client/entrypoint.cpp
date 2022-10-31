/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#include "Engine.hpp"
#include "NetworkClient.hpp"
#include "components/Direction.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/Weapon.hpp"
#include "components/client/Controllable.hpp"
#include "components/client/Drawable.hpp"
#include "components/client/Parallax.hpp"
#include "components/client/Animated.hpp"
#include "systems/ManageClientEvents.hpp"
#include "systems/Movement.hpp"
#include "systems/client/Draw.hpp"
#include "systems/client/HandleIncomingMessages.hpp"
#include "systems/client/HandleSFMLEvents.hpp"
#include "systems/client/HandleSFMLKeys.hpp"
#include "systems/client/SendDirection.hpp"
#include "systems/client/HandleParallaxBounds.hpp"

/**
 * This function is used to get the game part of the world.
 * Currently registering every components to the world's registry and adding every associated systems to the world
 * @param engine The engine in which you want to operate
 * @return The world ready to be used
 */
ecs::World getGameWorld(ecs::Engine &engine)
{
    ecs::World world(engine.getWindow());


    world.registry.registerComponent<ecs::component::EntityType>();
    world.registry.registerComponent<ecs::component::Velocity>();
    world.registry.registerComponent<ecs::component::Size>();
    world.registry.registerComponent<ecs::component::Faction>();
    world.registry.registerComponent<ecs::component::NetworkId>();
    world.registry.registerComponent<ecs::component::Position>();
    world.registry.registerComponent<ecs::component::Projectile>();
    world.registry.registerComponent<ecs::component::Direction>();
    world.registry.registerComponent<ecs::component::Weapon>();
    world.registry.registerComponent<ecs::component::Parallax>();
    world.registry.registerComponent<ecs::component::Health>();
    world.registry.registerComponent<ecs::component::Drawable>();
    world.registry.registerComponent<ecs::component::Shootable>();
    world.registry.registerComponent<ecs::component::Controllable>();
    world.registry.registerComponent<ecs::component::Animated>();

    world.addSystem(ecs::systems::handleSFMLEvents);
    world.addSystem(ecs::systems::handleSFMLKeys);
    world.addSystem(ecs::systems::manageClientEvents);
    world.addSystem(ecs::systems::draw);
    world.addSystem(ecs::systems::HandleIncomingMessages);
    world.addSystem(ecs::systems::SendDirection);
    world.addSystem(ecs::systems::movement);
    world.addSystem(ecs::systems::HandleParallaxBounds);

    ecs::Entity background1 = world.registry.spawn_entity();
    ecs::Entity backgroundp1 = world.registry.spawn_entity();
    ecs::Entity background2 = world.registry.spawn_entity();
    ecs::Entity backgroundp2 = world.registry.spawn_entity();
    ecs::Entity background3 = world.registry.spawn_entity();
    ecs::Entity backgroundp3 = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(background1, {0, 0});
    world.registry.addComponent<ecs::component::Size>(background1, {ecs::constant::mapHeight, ecs::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background1, {"bg1", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(background1, {1, 0});
    world.registry.addComponent<ecs::component::Direction>(background1, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(background1, {ecs::constant::mapWidth *-1, ecs::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(background1, {640, 0, 0, 0, 5760, 15, 0});
    world.registry.addComponent<ecs::component::Position>(backgroundp1, {ecs::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(backgroundp1, {ecs::constant::mapHeight, ecs::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(backgroundp1, {"bg1", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(backgroundp1, {1, 0});
    world.registry.addComponent<ecs::component::Direction>(backgroundp1, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(backgroundp1, {ecs::constant::mapWidth *-1, ecs::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(backgroundp1, {640, 0, 0, 0, 5760, 15, 0});
    world.registry.addComponent<ecs::component::Position>(background2, {0, 0});
    world.registry.addComponent<ecs::component::Size>(background2, {ecs::constant::mapHeight, ecs::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background2, {"bg2", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(background2, {2, 0});
    world.registry.addComponent<ecs::component::Direction>(background2, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(background2, {ecs::constant::mapWidth *-1, ecs::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(background2, {640, 0, 0, 0, 5760, 5, 0});
    world.registry.addComponent<ecs::component::Position>(backgroundp2, {ecs::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(backgroundp2, {ecs::constant::mapHeight, ecs::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(backgroundp2, {"bg2", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(backgroundp2, {2, 0});
    world.registry.addComponent<ecs::component::Parallax>(backgroundp2, {ecs::constant::mapWidth *-1, ecs::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Direction>(backgroundp2, {-1, 0});
    world.registry.addComponent<ecs::component::Animated>(backgroundp2, {640, 0, 0, 0, 5760, 5, 0});
    world.registry.addComponent<ecs::component::Position>(background3, {0, 0});
    world.registry.addComponent<ecs::component::Size>(background3, {ecs::constant::mapHeight, ecs::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background3, {"bg3", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(background3, {3, 0});
    world.registry.addComponent<ecs::component::Parallax>(background3, {ecs::constant::mapWidth *-1, ecs::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Direction>(background3, {-1, 0});
    world.registry.addComponent<ecs::component::Animated>(background3, {640, 0, 0, 0, 5760, 10, 0});
    world.registry.addComponent<ecs::component::Position>(backgroundp3, {ecs::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(backgroundp3, {ecs::constant::mapHeight, ecs::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(backgroundp3, {"bg3", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(backgroundp3, {3, 0});
    world.registry.addComponent<ecs::component::Direction>(backgroundp3, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(backgroundp3, {ecs::constant::mapWidth *-1, ecs::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(backgroundp3, {640, 0, 0, 0, 5760, 10, 0});
    return world;
}

/**
 * Main function of the client, running everything to start the game
 * @return 0 if no error, anything otherwise
 */
int main()
{
    asset::AssetLoader::LoadIniFile("./config.ini");
    network::Client::setHost("localhost");
    network::Client::setPort("8000");
    network::Client::connect();
    ecs::Engine engine;
    network::Message msg;
    msg.fill(0);

    engine.setWaitingWorld(getGameWorld(engine));
    network::Client::getOutgoingMessages().push(msg);

    engine.run();
    return 0;
}
