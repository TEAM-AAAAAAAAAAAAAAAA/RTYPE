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
#include "components/client/Animated.hpp"
#include "components/client/Controllable.hpp"
#include "components/client/Drawable.hpp"
#include "components/client/Hitbox.hpp"
#include "components/client/Parallax.hpp"
#include "systems/ManageClientEvents.hpp"
#include "systems/Movement.hpp"
#include "systems/client/Draw.hpp"
#include "systems/client/HandleIncomingMessages.hpp"
#include "systems/client/HandleParallaxBounds.hpp"
#include "systems/client/HandleSFMLEvents.hpp"
#include "systems/client/HandleSFMLKeys.hpp"
#include "systems/client/SendDirection.hpp"
#include "systems/client/Animate.hpp"

static void registerAllComponent(ecs::World &world)
{
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
    world.registry.registerComponent<ecs::component::Hitbox>();
}

static void addAllSystems(ecs::World &world)
{
    world.addSystem(ecs::systems::handleSFMLEvents);
    world.addSystem(ecs::systems::handleSFMLKeys);
    world.addSystem(ecs::systems::manageClientEvents);
    world.addSystem(ecs::systems::draw);
    world.addSystem(ecs::systems::HandleIncomingMessages);
    world.addSystem(ecs::systems::SendDirection);
    world.addSystem(ecs::systems::movement);
    world.addSystem(ecs::systems::HandleParallaxBounds);
}

static void setParallax(ecs::World &world)
{
    using AnimFrame = ecs::component::Animated::AnimFrame;

    ecs::Entity background1 = world.registry.spawn_entity();
    ecs::Entity parallaxFirstView = world.registry.spawn_entity();
    ecs::Entity background2 = world.registry.spawn_entity();
    ecs::Entity parallaxSecondView = world.registry.spawn_entity();
    ecs::Entity background3 = world.registry.spawn_entity();
    ecs::Entity parallaxThirdView = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(background1, {0, 0});
    world.registry.addComponent<ecs::component::Size>(background1, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background1, {"bg1", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(background1, {1, 0});
    world.registry.addComponent<ecs::component::Direction>(background1, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        background1, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(background1, AnimFrame(0, 0, 640, 360, 15));
    world.registry.addComponent<ecs::component::Position>(parallaxFirstView, {utils::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(
        parallaxFirstView, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(parallaxFirstView, {"bg1", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(parallaxFirstView, {1, 0});
    world.registry.addComponent<ecs::component::Direction>(parallaxFirstView, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        parallaxFirstView, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(parallaxFirstView, AnimFrame(0, 0, 640, 360, 15));
    world.registry.addComponent<ecs::component::Position>(background2, {0, 0});
    world.registry.addComponent<ecs::component::Size>(background2, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background2, {"bg2", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(background2, {2, 0});
    world.registry.addComponent<ecs::component::Direction>(background2, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        background2, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(background2, AnimFrame(0, 0, 640, 360, 5));
    world.registry.addComponent<ecs::component::Position>(parallaxSecondView, {utils::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(
        parallaxSecondView, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(parallaxSecondView, {"bg2", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(parallaxSecondView, {2, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        parallaxSecondView, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Direction>(parallaxSecondView, {-1, 0});
    world.registry.addComponent<ecs::component::Position>(background3, {0, 0});
    world.registry.addComponent<ecs::component::Size>(background3, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background3, {"bg3", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(background3, {3, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        background3, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Direction>(background3, {-1, 0});
    world.registry.addComponent<ecs::component::Animated>(background3, AnimFrame(0, 0, 640, 360, 10));
    world.registry.addComponent<ecs::component::Position>(parallaxThirdView, {utils::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(
        parallaxThirdView, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(parallaxThirdView, {"bg3", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Velocity>(parallaxThirdView, {3, 0});
    world.registry.addComponent<ecs::component::Direction>(parallaxThirdView, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        parallaxThirdView, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(parallaxThirdView, AnimFrame(0, 0, 640, 360, 10));
}

/**
 * This function is used to get the game part of the world.
 * Currently registering every components to the world's registry and adding every associated systems to the world
 * @param engine The engine in which you want to operate
 * @return The world ready to be used
 */
ecs::World getGameWorld()
{
    ecs::World world;

    registerAllComponent(world);
    addAllSystems(world);
    setParallax(world);
    return world;
}

/**
 * Main function of the client, running everything to start the game
 * @return 0 if no error, anything otherwise
 */
int main()
{
    asset::AssetLoader::LoadIniFile(asset::AssetLoader::smartPath("assets", "config.ini"));
    network::Client::setHost("localhost");
    network::Client::setPort("8000");
    network::Client::connect();
    utils::Window::get().setFramerateLimit(60);
    ecs::Engine engine;
    network::Message msg;
    msg.fill(0);

    ecs::WorldManager::setWaitingWorld(getGameWorld);
    network::Client::getOutgoingMessages().push(msg);

    engine.run();
    return 0;
}
