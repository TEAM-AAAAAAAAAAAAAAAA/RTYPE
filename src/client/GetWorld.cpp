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

static void setGameParallax(ecs::World &world)
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

    world.registry.addComponent<ecs::component::Velocity>(background1, {1, 0});
    world.registry.addComponent<ecs::component::Direction>(background1, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        background1, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(background1, AnimFrame(0, 0, 640, 360, 15));

    world.registry.addComponent<ecs::component::Position>(parallaxFirstView, {utils::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(
        parallaxFirstView, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(parallaxFirstView, {"bg1", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Activable>(parallaxFirstView, {});

    world.registry.addComponent<ecs::component::Velocity>(parallaxFirstView, {1, 0});
    world.registry.addComponent<ecs::component::Direction>(parallaxFirstView, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        parallaxFirstView, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(parallaxFirstView, AnimFrame(0, 0, 640, 360, 15));

    world.registry.addComponent<ecs::component::Position>(background2, {0, 0});
    world.registry.addComponent<ecs::component::Size>(
        background2, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background2, {"bg2", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Activable>(background2, {});

    world.registry.addComponent<ecs::component::Velocity>(background2, {2, 0});
    world.registry.addComponent<ecs::component::Direction>(background2, {-1, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        background2, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Animated>(background2, AnimFrame(0, 0, 640, 360, 5));

    world.registry.addComponent<ecs::component::Position>(parallaxSecondView, {utils::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(
        parallaxSecondView, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(parallaxSecondView, {"bg2", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Activable>(parallaxSecondView, {});

    world.registry.addComponent<ecs::component::Velocity>(parallaxSecondView, {2, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        parallaxSecondView, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Direction>(parallaxSecondView, {-1, 0});
    world.registry.addComponent<ecs::component::Animated>(parallaxSecondView, AnimFrame(0, 0, 640, 360, 5));

    world.registry.addComponent<ecs::component::Position>(background3, {0, 0});
    world.registry.addComponent<ecs::component::Size>(
        background3, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background3, {"bg3", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Activable>(background3, {});

    world.registry.addComponent<ecs::component::Velocity>(background3, {3, 0});
    world.registry.addComponent<ecs::component::Parallax>(
        background3, {utils::constant::mapWidth * -1, utils::constant::mapWidth * 2});
    world.registry.addComponent<ecs::component::Direction>(background3, {-1, 0});
    world.registry.addComponent<ecs::component::Animated>(background3, AnimFrame(0, 0, 640, 360, 10));

    world.registry.addComponent<ecs::component::Position>(parallaxThirdView, {utils::constant::mapWidth, 0});
    world.registry.addComponent<ecs::component::Size>(
        parallaxThirdView, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(parallaxThirdView, {"bg3", {0, 0, 5760, 360}});
    world.registry.addComponent<ecs::component::Activable>(parallaxThirdView, {});

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
ecs::World getGameWorld(const std::string &port = "8000", const std::string &host = "localhost")
{
    ecs::World world;

    audio::AudioManager::stopBGM();
    audio::AudioManager::loadBGM("bgm1");
    audio::AudioManager::playBGM();
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
    world.addSystem(ecs::systems::animate);
    world.addSystem(ecs::systems::HandleParallaxBounds);
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
        textFirstRoom, {itRoom->second.posX + 100, itRoom->second.posY - 0 + itRoom->second.rectHeight / 2});
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

static void setVolumeButtons(ecs::World &world)
{
    auto itLeftButton = utils::constant::buttonValueMap.find(utils::constant::SOUND_LEFT);
    auto itRightButton = utils::constant::buttonValueMap.find(utils::constant::SOUND_RIGHT);
    auto itMusicSlide = utils::constant::buttonValueMap.find(utils::constant::SLIDE_MUSIC);
    auto itSoundSlide = utils::constant::buttonValueMap.find(utils::constant::SLIDE_SOUND);
    auto itMusicBar = utils::constant::buttonValueMap.find(utils::constant::SOUND_BAR);
    ecs::Entity leftSound = world.registry.spawn_entity();
    ecs::Entity rightSound = world.registry.spawn_entity();
    ecs::Entity leftMusic = world.registry.spawn_entity();
    ecs::Entity rightMusic = world.registry.spawn_entity();
    ecs::Entity soundBar = world.registry.spawn_entity();
    ecs::Entity musicBar = world.registry.spawn_entity();
    ecs::Entity slideMusicButton = world.registry.spawn_entity();
    ecs::Entity slideSoundButton = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(leftSound, {itLeftButton->second.posX, itLeftButton->second.posY});
    world.registry.addComponent<ecs::component::Size>(leftSound, {itLeftButton->second.rectHeight, itLeftButton->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(leftSound, {"menu", {itLeftButton->second.rectLeft, itLeftButton->second.rectTop, itLeftButton->second.defaultRectWidth, itLeftButton->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(leftSound, {true, false, utils::constant::SOUND_LEFT});

    world.registry.addComponent<ecs::component::Position>(rightSound, {itRightButton->second.posX, itRightButton->second.posY});
    world.registry.addComponent<ecs::component::Size>(rightSound, {itRightButton->second.rectHeight, itRightButton->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(rightSound, {"menu", {itRightButton->second.rectLeft, itRightButton->second.rectTop, itRightButton->second.defaultRectWidth, itRightButton->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(rightSound, {true, true, utils::constant::SOUND_RIGHT});

    world.registry.addComponent<ecs::component::Position>(leftMusic, {itLeftButton->second.posX, itLeftButton->second.posY + 130});
    world.registry.addComponent<ecs::component::Size>(leftMusic, {itLeftButton->second.rectHeight, itLeftButton->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(leftMusic, {"menu", {itLeftButton->second.rectLeft, itLeftButton->second.rectTop, itLeftButton->second.defaultRectWidth, itLeftButton->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(leftMusic, {true, false, utils::constant::SOUND_LEFT});

    world.registry.addComponent<ecs::component::Position>(rightMusic, {itRightButton->second.posX, itRightButton->second.posY + 130});
    world.registry.addComponent<ecs::component::Size>(rightMusic, {itRightButton->second.rectHeight, itRightButton->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(rightMusic, {"menu", {itRightButton->second.rectLeft, itRightButton->second.rectTop, itRightButton->second.defaultRectWidth, itRightButton->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(rightMusic, {true, true, utils::constant::SOUND_RIGHT});

    world.registry.addComponent<ecs::component::Position>(soundBar, {itMusicBar->second.posX, itMusicBar->second.posY});
    world.registry.addComponent<ecs::component::Size>(soundBar, {itMusicBar->second.rectHeight, itMusicBar->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(soundBar, {"menu", {itMusicBar->second.rectLeft, itMusicBar->second.rectTop, itMusicBar->second.defaultRectWidth,itMusicBar->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(soundBar, {true, false, utils::constant::SOUND_BAR});

    world.registry.addComponent<ecs::component::Position>(musicBar, {itMusicBar->second.posX, itMusicBar->second.posY + 130});
    world.registry.addComponent<ecs::component::Size>(musicBar, {itMusicBar->second.rectHeight, itMusicBar->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(musicBar, {"menu", {itMusicBar->second.rectLeft, itMusicBar->second.rectTop, itMusicBar->second.defaultRectWidth,itMusicBar->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(musicBar, {true, false, utils::constant::SOUND_BAR});

    world.registry.addComponent<ecs::component::Position>(slideMusicButton, {itLeftButton->second.posX, itLeftButton->second.posY});
    world.registry.addComponent<ecs::component::Size>(slideMusicButton, {itLeftButton->second.rectHeight, itLeftButton->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(slideMusicButton, {"menu", {itLeftButton->second.rectLeft, itLeftButton->second.rectTop, itLeftButton->second.defaultRectWidth, itLeftButton->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(slideMusicButton, {false, false, utils::constant::OPTION_INTERFACE});


    world.registry.addComponent<ecs::component::Position>(slideSoundButton, {itSoundSlide->second.posX, itSoundSlide->second.posY});
    world.registry.addComponent<ecs::component::Size>(slideSoundButton, {itSoundSlide->second.rectHeight, itSoundSlide->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(slideSoundButton, {"menu", {itSoundSlide->second.rectLeft, itSoundSlide->second.rectTop, itSoundSlide->second.defaultRectWidth,itMusicSlide->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(slideSoundButton, {true, false, utils::constant::SLIDE_SOUND});
}

static void setOptionInterface(ecs::World &world)
{
    auto itOptionInterface = utils::constant::buttonValueMap.find(utils::constant::OPTION_INTERFACE);
    ecs::Entity optionInterface = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(optionInterface, {itOptionInterface->second.posX, itOptionInterface->second.posY});
    world.registry.addComponent<ecs::component::Size>(optionInterface, {itOptionInterface->second.rectHeight, itOptionInterface->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(optionInterface, {"menu", {itOptionInterface->second.rectLeft, itOptionInterface->second.rectTop, itOptionInterface->second.defaultRectWidth, itOptionInterface->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(optionInterface, {true, false, utils::constant::OPTION_INTERFACE});
}

static void setHowToPlayButton(ecs::World &world)
{

}

static void setMenuBackground(ecs::World &world)
{
    ecs::Entity planet = world.registry.spawn_entity();
    int width = 7392;
    int height = 96;
    int nbFrame = 77;
    int delay = 75;

    world.registry.addComponent<ecs::component::Position>(planet, {1200, utils::constant::mapHeight / 8});
    world.registry.addComponent<ecs::component::Size>(planet, {height * 8, (width / nbFrame) * 8});
    world.registry.addComponent<ecs::component::Drawable>(planet, {"planet", {0, 0, (width / nbFrame), height}});
    world.registry.addComponent<ecs::component::Activable>(planet, {});
    world.registry.addComponent<ecs::component::Animated>(planet,
        {
            AnimFrame(0, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 2, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 3, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 4, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 5, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 6, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 7, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 8, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 9, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 10, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 11, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 12, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 13, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 14, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 15, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 16, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 17, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 18, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 19, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 20, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 21, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 22, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 23, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 24, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 25, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 26, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 27, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 28, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 29, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 30, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 31, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 32, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 33, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 34, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 35, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 36, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 37, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 38, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 39, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 40, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 41, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 42, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 43, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 44, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 45, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 46, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 47, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 48, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 49, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 50, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 51, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 52, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 53, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 54, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 55, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 56, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 57, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 58, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 59, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 60, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 61, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 62, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 63, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 64, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 65, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 66, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 67, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 68, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 69, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 70, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 71, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 72, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 73, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 74, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 75, 0, (width / nbFrame), height, delay),
            AnimFrame(width / nbFrame * 76, 0, (width / nbFrame), height, delay),
        });
}

static void setMenu(ecs::World &world)
{
    setGameParallax(world);
    setMenuBackground(world);
    setMainButtons(world);
    setRoomButtons(world);
    setRoomTexts(world);
    setOptionInterface(world);
    setVolumeButtons(world);
    setHowToPlayButton(world);
}

ecs::World getMenuWorld()
{
    ecs::World world;

    utils::Window::getInstance().setFramerateLimit(FRAME_LIMIT);
    utils::Window::Color = sf::Color(18, 32, 45, 255);
    audio::AudioManager::stopBGM();
    audio::AudioManager::loadBGM("lobby_bgm");
    audio::AudioManager::playBGM("lobby_bgm");
    registerComponents(world);
    addMenuSystems(world);
    setMenu(world);
    return world;
}

#pragma endregion MenuWorld