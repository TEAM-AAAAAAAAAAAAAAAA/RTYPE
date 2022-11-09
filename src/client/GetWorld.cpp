/*
** EPITECH PROJECT, by hourcadettej on 11/6/22.
** rtype
** File description:
** rtype
*/

#include "GetWorld.hpp"
#include "NetworkClient.hpp"
#include "components/Direction.hpp"
#include "components/Faction.hpp"
#include "components/Health.hpp"
#include "components/Position.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/Weapon.hpp"
#include "components/client/Activable.hpp"
#include "components/client/Animated.hpp"
#include "components/client/Controllable.hpp"
#include "components/client/Drawable.hpp"
#include "components/client/Hitbox.hpp"
#include "components/client/Parallax.hpp"
#include "systems/ManageClientEvents.hpp"
#include "systems/Movement.hpp"
#include "systems/client/Buttons.hpp"
#include "systems/client/Draw.hpp"
#include "systems/client/HandleIncomingMessages.hpp"
#include "systems/client/HandleParallaxBounds.hpp"
#include "systems/client/HandleSFMLEvents.hpp"
#include "systems/client/HandleSFMLKeys.hpp"
#include "systems/client/SendDirection.hpp"
#include "systems/client/Score.hpp"

static const int FRAME_LIMIT = 60;

#pragma region GameWorld

static void registerComponents(ecs::World &world)
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
    world.registry.registerComponent<ecs::component::Text>();
    world.registry.registerComponent<ecs::component::Activable>();
}

static void addGameSystems(ecs::World &world)
{
    world.addSystem(ecs::systems::handleSFMLEvents);
    world.addSystem(ecs::systems::handleSFMLKeys);
    world.addSystem(ecs::systems::manageClientEvents);
    world.addSystem(ecs::systems::draw);
    world.addSystem(ecs::systems::HandleIncomingMessages);
    world.addSystem(ecs::systems::SendDirection);
    world.addSystem(ecs::systems::movement);
    world.addSystem(ecs::systems::HandleParallaxBounds);
    world.addSystem(ecs::systems::score);
}

static void setGameTexts(ecs::World &world)
{
    ecs::Entity textScore = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(textScore, {10, 10});
    world.registry.addComponent<ecs::component::Size>(textScore, {60, 60});
    world.registry.addComponent<ecs::component::Text>(textScore, ecs::component::Text("Score: ", "nasa"));
}
static void setGameParallax(ecs::World &world)
{
    using AnimFrame = ecs::component::Animated::AnimFrame;

    ecs::Entity background1 = world.registry.spawn_entity();
    ecs::Entity parallaxFirstView = world.registry.spawn_entity();
    ecs::Entity background2 = world.registry.spawn_entity();
    ecs::Entity parallaxSecondView = world.registry.spawn_entity();
    ecs::Entity background3 = world.registry.spawn_entity();
    ecs::Entity parallaxThirdView = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(background1, {0, 0});
    world.registry.addComponent<ecs::component::Size>(
        background1, {utils::constant::mapHeight, utils::constant::mapWidth});
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
    world.registry.addComponent<ecs::component::Size>(
        background2, {utils::constant::mapHeight, utils::constant::mapWidth});
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
    world.registry.addComponent<ecs::component::Animated>(parallaxSecondView, AnimFrame(0, 0, 640, 360, 5));
    world.registry.addComponent<ecs::component::Position>(background3, {0, 0});
    world.registry.addComponent<ecs::component::Size>(
        background3, {utils::constant::mapHeight, utils::constant::mapWidth});
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
ecs::World getGameWorld(/*const std::string &port, const std::string &host*/)
{
    ecs::World world;
    network::Message msg;
    std::string port = "8000";
    std::string host = "localhost";

    network::Client::setHost(host);
    network::Client::setPort(port);
    network::Client::connect();
    utils::Window::getInstance().setFramerateLimit(FRAME_LIMIT);
    msg.fill(0);
    registerComponents(world);
    addGameSystems(world);
    setGameParallax(world);
    setGameTexts(world);
    network::Client::getOutgoingMessages().push(msg);
    return world;
}
#pragma endregion GameWorld

#pragma region MenuWorld
static void addMenuSystems(ecs::World &world)
{
    world.addSystem(ecs::systems::handleSFMLEvents);
    world.addSystem(ecs::systems::handleSFMLKeys);
    world.addSystem(ecs::systems::manageClientEvents);
    world.addSystem(ecs::systems::draw);
    world.addSystem(ecs::systems::movement);
    world.addSystem(ecs::systems::buttons);
}

static void setMenuBackground(ecs::World &world)
{
    ecs::Entity playButton = world.registry.spawn_entity();
    ecs::Entity optionButton = world.registry.spawn_entity();
    ecs::Entity quitButton = world.registry.spawn_entity();
    ecs::Entity player = world.registry.spawn_entity();
    ecs::Entity text = world.registry.spawn_entity();

    int buttonWidth = 600;
    int buttonHeight = 150;

    std::cout << "Setting menu background" << std::endl;
    world.registry.addComponent<ecs::component::Position>(
        player, {(utils::constant::mapWidth / 2 - buttonWidth), (utils::constant::mapHeight / 3) - buttonHeight / 2});
    world.registry.addComponent<ecs::component::Size>(player, {100, 200});
    world.registry.addComponent<ecs::component::Drawable>(player, {"players", {1, 1, 32, 16}});
    world.registry.addComponent<ecs::component::Controllable>(
        player, {sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::H});
    std::cout << "Setting menu 2 background" << std::endl;
    world.registry.addComponent<ecs::component::Position>(playButton,
        {utils::constant::mapWidth / 2 - buttonWidth / 2, (utils::constant::mapHeight / 3) - buttonHeight / 2});
    world.registry.addComponent<ecs::component::Size>(playButton, {buttonHeight, buttonWidth});
    world.registry.addComponent<ecs::component::Drawable>(playButton, {"menu", {324, 2079, 916, 292}});
    world.registry.addComponent<ecs::component::Activable>(
        playButton, ecs::component::Activable(utils::constant::PLAY, true));

    world.registry.addComponent<ecs::component::Position>(optionButton,
        {utils::constant::mapWidth / 2 - buttonWidth / 2, (utils::constant::mapHeight / 3 + 300) - buttonHeight / 2});
    world.registry.addComponent<ecs::component::Size>(optionButton, {buttonHeight, buttonWidth});
    world.registry.addComponent<ecs::component::Drawable>(optionButton, {"menu", {3651, 2079, 916, 292}});
    world.registry.addComponent<ecs::component::Activable>(
        optionButton, ecs::component::Activable(utils::constant::OPTIONS));

    world.registry.addComponent<ecs::component::Position>(quitButton,
        {utils::constant::mapWidth / 2 - buttonWidth / 2, (utils::constant::mapHeight / 3 + 500) - buttonHeight / 2});
    world.registry.addComponent<ecs::component::Size>(quitButton, {buttonHeight, buttonWidth});
    world.registry.addComponent<ecs::component::Drawable>(quitButton, {"menu", {4760, 2079, 916, 292}});
    world.registry.addComponent<ecs::component::Activable>(
        quitButton, ecs::component::Activable(utils::constant::QUIT));
}

static void destroyMenu(ecs::World &world) {}

ecs::World getMenuWorld()
{
    ecs::World world;

    utils::Window::getInstance().setFramerateLimit(FRAME_LIMIT);
    utils::Window::Color = sf::Color(18, 32, 45, 255);
    registerComponents(world);
    addMenuSystems(world);
    setMenuBackground(world);
    return world;
}

#pragma endregion MenuWorld