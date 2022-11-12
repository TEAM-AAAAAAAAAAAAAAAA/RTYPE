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
#include "components/Score.hpp"
#include "components/Size.hpp"
#include "components/Velocity.hpp"
#include "components/Weapon.hpp"
#include "components/client/Activable.hpp"
#include "components/client/Animated.hpp"
#include "components/client/Controllable.hpp"
#include "components/client/Drawable.hpp"
#include "components/client/Hitbox.hpp"
#include "components/client/Parallax.hpp"
#include "components/client/Text.hpp"
#include "systems/ManageClientEvents.hpp"
#include "systems/Movement.hpp"
#include "systems/client/Animate.hpp"
#include "systems/client/Draw.hpp"
#include "systems/client/ExecuteOnce.hpp"
#include "systems/client/HandleIncomingMessages.hpp"
#include "systems/client/HandleParallaxBounds.hpp"
#include "systems/client/HandleSFMLEvents.hpp"
#include "systems/client/HandleSFMLKeys.hpp"
#include "systems/client/HealthBar.hpp"
#include "systems/client/MenuSelect.hpp"
#include "systems/client/ScoreUpdate.hpp"
#include "systems/client/SendDirection.hpp"

static const int FRAME_LIMIT = 60;
using AnimFrame = ecs::component::Animated::AnimFrame;

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
    world.registry.registerComponent<ecs::component::Score>();
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
    world.addSystem(ecs::systems::scoreUpdate);
    world.addSystem(ecs::systems::executeOnce);
    world.addSystem(ecs::systems::healthBar);
    world.addSystem(ecs::systems::animate);
}

static void setGameHUD(ecs::World &world)
{
    ecs::Entity textScore = world.registry.spawn_entity();
    ecs::Entity health = world.registry.spawn_entity();
    ecs::Entity healthBar = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(textScore, {10, 10});
    world.registry.addComponent<ecs::component::Size>(textScore, {40, 15});
    world.registry.addComponent<ecs::component::Text>(textScore, {});
    world.registry.addComponent<ecs::component::Score>(textScore, {});
    world.registry.addComponent<ecs::component::Activable>(textScore, {});

    world.registry.addComponent<ecs::component::Position>(health, {6, 900});
    world.registry.addComponent<ecs::component::Size>(health, {100, 400});
    world.registry.addComponent<ecs::component::Drawable>(health, {"menu", {3475, 844, 1011, 256}});
    world.registry.addComponent<ecs::component::Activable>(health, {});

    world.registry.addComponent<ecs::component::Position>(healthBar, {118, 922});
    world.registry.addComponent<ecs::component::Size>(healthBar, {50, 282});
    world.registry.addComponent<ecs::component::Drawable>(healthBar, {"menu", {3767, 719, 714, 97}});
    world.registry.addComponent<ecs::component::Health>(healthBar, {utils::constant::maxPlayerHealth});
    world.registry.addComponent<ecs::component::Activable>(healthBar, {});
}

static void setGameParallax(ecs::World &world, bool moving = true)
{
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
    world.registry.addComponent<ecs::component::Activable>(background1, {});
    if (moving) {
        world.registry.addComponent<ecs::component::Velocity>(background1, {1, 0});
        world.registry.addComponent<ecs::component::Direction>(background1, {-1, 0});
        world.registry.addComponent<ecs::component::Parallax>(
            background1, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
        world.registry.addComponent<ecs::component::Animated>(background1, AnimFrame(0, 0, 640, 360, 15));
    }
    world.registry.addComponent<ecs::component::Position>(parallaxFirstView, {utils::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(
        parallaxFirstView, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(parallaxFirstView, {"bg1", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Activable>(parallaxFirstView, {});
    if (moving) {
        world.registry.addComponent<ecs::component::Velocity>(parallaxFirstView, {1, 0});
        world.registry.addComponent<ecs::component::Direction>(parallaxFirstView, {-1, 0});
        world.registry.addComponent<ecs::component::Parallax>(
            parallaxFirstView, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
        world.registry.addComponent<ecs::component::Animated>(parallaxFirstView, AnimFrame(0, 0, 640, 360, 15));
    }
    world.registry.addComponent<ecs::component::Position>(background2, {0, 0});
    world.registry.addComponent<ecs::component::Size>(
        background2, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background2, {"bg2", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Activable>(background2, {});
    if (moving) {
        world.registry.addComponent<ecs::component::Velocity>(background2, {2, 0});
        world.registry.addComponent<ecs::component::Direction>(background2, {-1, 0});
        world.registry.addComponent<ecs::component::Parallax>(
            background2, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
        world.registry.addComponent<ecs::component::Animated>(background2, AnimFrame(0, 0, 640, 360, 5));
    }
    world.registry.addComponent<ecs::component::Position>(parallaxSecondView, {utils::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(
        parallaxSecondView, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(parallaxSecondView, {"bg2", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Activable>(parallaxSecondView, {});
    if (moving) {
        world.registry.addComponent<ecs::component::Velocity>(parallaxSecondView, {2, 0});
        world.registry.addComponent<ecs::component::Parallax>(
            parallaxSecondView, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
        world.registry.addComponent<ecs::component::Direction>(parallaxSecondView, {-1, 0});
        world.registry.addComponent<ecs::component::Animated>(parallaxSecondView, AnimFrame(0, 0, 640, 360, 5));
    }
    world.registry.addComponent<ecs::component::Position>(background3, {0, 0});
    world.registry.addComponent<ecs::component::Size>(
        background3, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background3, {"bg3", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Activable>(background3, {});
    if (moving) {
        world.registry.addComponent<ecs::component::Velocity>(background3, {3, 0});
        world.registry.addComponent<ecs::component::Parallax>(
            background3, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
        world.registry.addComponent<ecs::component::Direction>(background3, {-1, 0});
        world.registry.addComponent<ecs::component::Animated>(background3, AnimFrame(0, 0, 640, 360, 10));
    }
    world.registry.addComponent<ecs::component::Position>(parallaxThirdView, {utils::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(
        parallaxThirdView, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(parallaxThirdView, {"bg3", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Activable>(parallaxThirdView, {});
    if (moving) {
        world.registry.addComponent<ecs::component::Velocity>(parallaxThirdView, {3, 0});
        world.registry.addComponent<ecs::component::Direction>(parallaxThirdView, {-1, 0});
        world.registry.addComponent<ecs::component::Parallax>(
            parallaxThirdView, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
        world.registry.addComponent<ecs::component::Animated>(parallaxThirdView, AnimFrame(0, 0, 640, 360, 10));
    }
}

/**
 * This function is used to get the game part of the world.
 * Currently registering every components to the world's registry and adding every associated systems to the world
 * @param engine The engine in which you want to operate
 * @return The world ready to be used
 */
ecs::World getGameWorld(const std::string &port = "8000", const std::string &host = "localhost")
{
    ecs::World world;

    network::Client::setHost(host);
    network::Client::setPort(port);
    utils::Window::getInstance().setFramerateLimit(FRAME_LIMIT);
    registerComponents(world);
    setGameParallax(world);
    setGameHUD(world);
    addGameSystems(world);
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
    world.addSystem(ecs::systems::menuSelect);
}

static void setMainButtons(ecs::World &world)
{
    ecs::Entity playButton = world.registry.spawn_entity();
    ecs::Entity optionButton = world.registry.spawn_entity();
    ecs::Entity quitButton = world.registry.spawn_entity();
    auto itPlay = utils::constant::buttonValueMap.find(utils::constant::PLAY);
    auto itOptions = utils::constant::buttonValueMap.find(utils::constant::OPTION);
    auto itQuit = utils::constant::buttonValueMap.find(utils::constant::QUIT);

    world.registry.addComponent<ecs::component::Position>(playButton, {itPlay->second.posX, itPlay->second.posY});
    world.registry.addComponent<ecs::component::Size>(
        playButton, {itPlay->second.rectHeight, itPlay->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(playButton,
        {"menu",
            {itPlay->second.rectLeft, itPlay->second.rectTop, itPlay->second.defaultRectWidth,
                itPlay->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(playButton, {true, true, utils::constant::PLAY});

    world.registry.addComponent<ecs::component::Position>(
        optionButton, {itOptions->second.posX, itOptions->second.posY});
    world.registry.addComponent<ecs::component::Size>(
        optionButton, {itPlay->second.rectHeight, itPlay->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(optionButton,
        {"menu",
            {itOptions->second.rectLeft, itOptions->second.rectTop, itPlay->second.defaultRectWidth,
                itPlay->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(optionButton, {true, true, utils::constant::OPTION});

    world.registry.addComponent<ecs::component::Position>(quitButton, {itQuit->second.posX, itQuit->second.posY});
    world.registry.addComponent<ecs::component::Size>(
        quitButton, {itPlay->second.rectHeight, itPlay->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(quitButton,
        {"menu",
            {itQuit->second.rectLeft, itQuit->second.rectTop, itPlay->second.defaultRectWidth,
                itPlay->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(quitButton, {true, true, utils::constant::QUIT});
}

static void setRoomTexts(ecs::World &world)
{
    ecs::Entity textFirstRoom = world.registry.spawn_entity();
    ecs::Entity textSecondRoom = world.registry.spawn_entity();
    ecs::Entity textThirdRoom = world.registry.spawn_entity();
    ecs::Entity textFourthRoom = world.registry.spawn_entity();
    auto itRoom = utils::constant::buttonValueMap.find(utils::constant::ROOM);

    world.registry.addComponent<ecs::component::Text>(textFirstRoom, {10});
    world.registry.addComponent<ecs::component::Text>(textSecondRoom, {10});
    world.registry.addComponent<ecs::component::Text>(textThirdRoom, {10});
    world.registry.addComponent<ecs::component::Text>(textFourthRoom, {10});
    world.registry.addComponent<ecs::component::Position>(
        textFirstRoom, {itRoom->second.posX + 100, itRoom->second.posY - 17 + itRoom->second.rectHeight / 2});
    world.registry.addComponent<ecs::component::Position>(
        textSecondRoom, {itRoom->second.posX + 100, itRoom->second.posY + 103 + itRoom->second.rectHeight / 2});
    world.registry.addComponent<ecs::component::Position>(
        textThirdRoom, {itRoom->second.posX + 100, itRoom->second.posY + 223 + itRoom->second.rectHeight / 2});
    world.registry.addComponent<ecs::component::Position>(
        textFourthRoom, {itRoom->second.posX + 100, itRoom->second.posY + 343 + itRoom->second.rectHeight / 2});
    world.registry.addComponent<ecs::component::Size>(textFirstRoom, {30, 0});
    world.registry.addComponent<ecs::component::Size>(textSecondRoom, {30, 0});
    world.registry.addComponent<ecs::component::Size>(textThirdRoom, {30, 0});
    world.registry.addComponent<ecs::component::Size>(textFourthRoom, {30, 0});
    world.registry.addComponent<ecs::component::Activable>(textFirstRoom, {false, false, utils::constant::ROOM_TEXT});
    world.registry.addComponent<ecs::component::Activable>(textSecondRoom, {false, false, utils::constant::ROOM_TEXT});
    world.registry.addComponent<ecs::component::Activable>(textThirdRoom, {false, false, utils::constant::ROOM_TEXT});
    world.registry.addComponent<ecs::component::Activable>(textFourthRoom, {false, false, utils::constant::ROOM_TEXT});
}

static void setRoomButtons(ecs::World &world)
{
    auto itRoom = utils::constant::buttonValueMap.find(utils::constant::ROOM);
    ecs::Entity firstRoom = world.registry.spawn_entity();
    ecs::Entity secondRoom = world.registry.spawn_entity();
    ecs::Entity thirdRoom = world.registry.spawn_entity();
    ecs::Entity fourthRoom = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(firstRoom, {itRoom->second.posX, itRoom->second.posY});
    world.registry.addComponent<ecs::component::Size>(firstRoom, {itRoom->second.rectHeight, itRoom->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(firstRoom,
        {"menu",
            {itRoom->second.rectLeft, itRoom->second.rectTop, itRoom->second.defaultRectWidth,
                itRoom->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(firstRoom, {false, true, utils::constant::ROOM});

    world.registry.addComponent<ecs::component::Position>(secondRoom, {itRoom->second.posX, itRoom->second.posY + 120});
    world.registry.addComponent<ecs::component::Size>(
        secondRoom, {itRoom->second.rectHeight, itRoom->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(secondRoom,
        {"menu",
            {itRoom->second.rectLeft, itRoom->second.rectTop, itRoom->second.defaultRectWidth,
                itRoom->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(secondRoom, {false, true, utils::constant::ROOM});

    world.registry.addComponent<ecs::component::Position>(thirdRoom, {itRoom->second.posX, itRoom->second.posY + 240});
    world.registry.addComponent<ecs::component::Size>(thirdRoom, {itRoom->second.rectHeight, itRoom->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(thirdRoom,
        {"menu",
            {itRoom->second.rectLeft, itRoom->second.rectTop, itRoom->second.defaultRectWidth,
                itRoom->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(thirdRoom, {false, true, utils::constant::ROOM});

    world.registry.addComponent<ecs::component::Position>(fourthRoom, {itRoom->second.posX, itRoom->second.posY + 360});
    world.registry.addComponent<ecs::component::Size>(
        fourthRoom, {itRoom->second.rectHeight, itRoom->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(fourthRoom,
        {"menu",
            {itRoom->second.rectLeft, itRoom->second.rectTop, itRoom->second.defaultRectWidth,
                itRoom->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(fourthRoom, {false, true, utils::constant::ROOM});
}

static void setMenuBackground(ecs::World &world)
{
    ecs::Entity planet = world.registry.spawn_entity();
    int delay = 20;

    world.registry.addComponent<ecs::component::Position>(planet, {900, utils::constant::mapHeight / 2});
    world.registry.addComponent<ecs::component::Size>(planet, {62 * 4, 93 * 4});
    world.registry.addComponent<ecs::component::Drawable>(planet, {"planet", {17, 17, (7258 / 78), 62}});
    world.registry.addComponent<ecs::component::Activable>(planet, {});
    world.registry.addComponent<ecs::component::Animated>(planet,
        {
            AnimFrame(17, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 2, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 3, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 4, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 5, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 6, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 7, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 8, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 9, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 10, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 11, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 12, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 13, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 14, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 15, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 16, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 17, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 18, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 19, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 20, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 21, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 22, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 23, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 24, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 25, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 26, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 27, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 28, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 29, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 30, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 31, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 32, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 33, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 34, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 35, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 36, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 37, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 38, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 39, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 40, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 41, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 42, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 43, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 44, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 45, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 46, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 47, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 48, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 49, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 50, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 51, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 52, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 53, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 54, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 55, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 56, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 57, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 58, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 59, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 60, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 61, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 62, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 63, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 64, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 65, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 66, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 67, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 68, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 69, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 70, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 71, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 72, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 73, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 74, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 75, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 76, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 77, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 78, 17, (7258 / 78), 62, delay),
            AnimFrame(17 + 7258 / 78 * 79, 17, (7258 / 78), 62, delay),
        });
}

static void setMenu(ecs::World &world)
{
    setGameParallax(world, false);
    setMenuBackground(world);
    setMainButtons(world);
    setRoomButtons(world);
    setRoomTexts(world);
}

ecs::World getMenuWorld()
{
    ecs::World world;

    utils::Window::getInstance().setFramerateLimit(FRAME_LIMIT);
    utils::Window::Color = sf::Color(18, 32, 45, 255);
    registerComponents(world);
    addMenuSystems(world);
    setMenu(world);
    return world;
}

#pragma endregion MenuWorld