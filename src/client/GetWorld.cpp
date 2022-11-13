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
#include "components/client/Connection.hpp"
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
#include "systems/client/PeriodicPing.hpp"
#include "systems/client/KeepAlive.hpp"
#include "systems/client/ExecuteOnce.hpp"

using AnimFrame = ecs::component::Animated::AnimFrame;
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
    world.registry.registerComponent<ecs::component::Score>();
    world.registry.registerComponent<ecs::component::Connection>();
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
    world.addSystem(ecs::systems::keepAlive);
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
    world.registry.addComponent<ecs::component::Text>(textScore, {"Score: "});
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
    world.registry.addComponent<ecs::component::Size>(playButton, {itPlay->second.rectHeight, itPlay->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(playButton, {"menu", {itPlay->second.rectLeft, itPlay->second.rectTop, itPlay->second.defaultRectWidth, itPlay->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(playButton, {true, true, utils::constant::PLAY});

    world.registry.addComponent<ecs::component::Position>(optionButton, {itOptions->second.posX, itOptions->second.posY});
    world.registry.addComponent<ecs::component::Size>(optionButton, {itPlay->second.rectHeight, itPlay->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(optionButton, {"menu", {itOptions->second.rectLeft, itOptions->second.rectTop, itPlay->second.defaultRectWidth, itPlay->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(optionButton, {true, true, utils::constant::OPTION});

    world.registry.addComponent<ecs::component::Position>(quitButton, {itQuit->second.posX, itQuit->second.posY});
    world.registry.addComponent<ecs::component::Size>(quitButton, {itPlay->second.rectHeight, itPlay->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(quitButton, {"menu", {itQuit->second.rectLeft, itQuit->second.rectTop, itPlay->second.defaultRectWidth, itPlay->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(quitButton, {true, true, utils::constant::QUIT});
}

static void setRoomTexts(ecs::World &world)
{
    ecs::Entity textFirstRoom = world.registry.spawn_entity();
    ecs::Entity textSecondRoom = world.registry.spawn_entity();
    ecs::Entity textThirdRoom = world.registry.spawn_entity();
    ecs::Entity textFourthRoom = world.registry.spawn_entity();
    auto itRoom = utils::constant::buttonValueMap.find(utils::constant::ROOM);

    world.registry.addComponent<ecs::component::Text>(textFirstRoom, {"0", "/", "4", "Player"});
    world.registry.addComponent<ecs::component::Text>(textSecondRoom, {"0", "/", "4", "Player"});
    world.registry.addComponent<ecs::component::Text>(textThirdRoom, {"0", "/", "4", "Player"});
    world.registry.addComponent<ecs::component::Text>(textFourthRoom, {"0", "/", "4", "Player"});
    world.registry.addComponent<ecs::component::Position>(textFirstRoom, {itRoom->second.posX + 100, itRoom->second.posY - 17 + itRoom->second.rectHeight / 2});
    world.registry.addComponent<ecs::component::Position>(textSecondRoom, {itRoom->second.posX + 100, itRoom->second.posY + 133 + itRoom->second.rectHeight / 2});
    world.registry.addComponent<ecs::component::Position>(textThirdRoom, {itRoom->second.posX + 100, itRoom->second.posY + 283 + itRoom->second.rectHeight / 2});
    world.registry.addComponent<ecs::component::Position>(textFourthRoom, {itRoom->second.posX + 100, itRoom->second.posY + 433 + itRoom->second.rectHeight / 2});
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
    world.registry.addComponent<ecs::component::Drawable>(firstRoom, {"menu", {itRoom->second.rectLeft, itRoom->second.rectTop, itRoom->second.defaultRectWidth, itRoom->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(firstRoom, {false, true, utils::constant::ROOM});
    world.registry.addComponent<ecs::component::Connection>(firstRoom, {});

    world.registry.addComponent<ecs::component::Position>(secondRoom, {itRoom->second.posX, itRoom->second.posY + 150});
    world.registry.addComponent<ecs::component::Size>(secondRoom, {itRoom->second.rectHeight, itRoom->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(secondRoom, {"menu", {itRoom->second.rectLeft, itRoom->second.rectTop, itRoom->second.defaultRectWidth, itRoom->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(secondRoom, {false, true, utils::constant::ROOM});
    world.registry.addComponent<ecs::component::Connection>(firstRoom, {});

    world.registry.addComponent<ecs::component::Position>(thirdRoom, {itRoom->second.posX, itRoom->second.posY + 300});
    world.registry.addComponent<ecs::component::Size>(thirdRoom, {itRoom->second.rectHeight, itRoom->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(thirdRoom, {"menu", {itRoom->second.rectLeft, itRoom->second.rectTop, itRoom->second.defaultRectWidth, itRoom->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(thirdRoom, {false, true, utils::constant::ROOM});
    world.registry.addComponent<ecs::component::Connection>(firstRoom, {});

    world.registry.addComponent<ecs::component::Position>(fourthRoom, {itRoom->second.posX, itRoom->second.posY + 450});
    world.registry.addComponent<ecs::component::Size>(fourthRoom, {itRoom->second.rectHeight, itRoom->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(fourthRoom, {"menu", {itRoom->second.rectLeft, itRoom->second.rectTop, itRoom->second.defaultRectWidth, itRoom->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(fourthRoom, {false, true, utils::constant::ROOM});
    world.registry.addComponent<ecs::component::Connection>(firstRoom, {});
}

static void setVolumeButtons(ecs::World &world)
{
    auto itLeftSound = utils::constant::buttonValueMap.find(utils::constant::SOUND_LEFT);
    auto itRightSound = utils::constant::buttonValueMap.find(utils::constant::SOUND_RIGHT);
    auto itLeftMusic = utils::constant::buttonValueMap.find(utils::constant::MUSIC_LEFT);
    auto itRightMusic = utils::constant::buttonValueMap.find(utils::constant::MUSIC_RIGHT);
    auto itMusicSlide = utils::constant::buttonValueMap.find(utils::constant::SLIDE_MUSIC);
    auto itSoundSlide = utils::constant::buttonValueMap.find(utils::constant::SLIDE_SOUND);
    auto itMusicBar = utils::constant::buttonValueMap.find(utils::constant::SOUND_BAR);
    auto itSetting = utils::constant::buttonValueMap.find(utils::constant::SETTINGS);
    auto itHowTo = utils::constant::buttonValueMap.find(utils::constant::HOW_TO);
    ecs::Entity leftSound = world.registry.spawn_entity();
    ecs::Entity rightSound = world.registry.spawn_entity();
    ecs::Entity leftMusic = world.registry.spawn_entity();
    ecs::Entity rightMusic = world.registry.spawn_entity();
    ecs::Entity soundBar = world.registry.spawn_entity();
    ecs::Entity musicBar = world.registry.spawn_entity();
    ecs::Entity slideMusicButton = world.registry.spawn_entity();
    ecs::Entity slideSoundButton = world.registry.spawn_entity();
    ecs::Entity settingsButton = world.registry.spawn_entity();
    ecs::Entity howToPlayButton = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(leftSound, {itLeftSound->second.posX, itLeftSound->second.posY});
    world.registry.addComponent<ecs::component::Size>(leftSound, {itLeftSound->second.rectHeight, itLeftSound->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(leftSound, {"menu", {itLeftSound->second.rectLeft, itLeftSound->second.rectTop, itLeftSound->second.defaultRectWidth, itLeftSound->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(leftSound, {false, true, utils::constant::SOUND_LEFT});

    world.registry.addComponent<ecs::component::Position>(rightSound, {itRightSound->second.posX, itRightSound->second.posY});
    world.registry.addComponent<ecs::component::Size>(rightSound, {itRightSound->second.rectHeight, itRightSound->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(rightSound, {"menu", {itRightSound->second.rectLeft, itRightSound->second.rectTop, itRightSound->second.defaultRectWidth, itRightSound->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(rightSound, {false, true, utils::constant::SOUND_RIGHT});

    world.registry.addComponent<ecs::component::Position>(leftMusic, {itLeftMusic->second.posX, itLeftMusic->second.posY});
    world.registry.addComponent<ecs::component::Size>(leftMusic, {itLeftMusic->second.rectHeight, itLeftMusic->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(leftMusic, {"menu", {itLeftMusic->second.rectLeft, itLeftMusic->second.rectTop, itLeftMusic->second.defaultRectWidth, itLeftMusic->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(leftMusic, {false, true, utils::constant::MUSIC_LEFT});

    world.registry.addComponent<ecs::component::Position>(rightMusic, {itRightMusic->second.posX, itRightMusic->second.posY});
    world.registry.addComponent<ecs::component::Size>(rightMusic, {itRightMusic->second.rectHeight, itRightMusic->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(rightMusic, {"menu", {itRightMusic->second.rectLeft, itRightMusic->second.rectTop, itRightMusic->second.defaultRectWidth, itRightMusic->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(rightMusic, {false, true, utils::constant::MUSIC_RIGHT});

    world.registry.addComponent<ecs::component::Position>(soundBar, {itMusicBar->second.posX, itMusicBar->second.posY});
    world.registry.addComponent<ecs::component::Size>(soundBar, {itMusicBar->second.rectHeight, itMusicBar->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(soundBar, {"menu", {itMusicBar->second.rectLeft, itMusicBar->second.rectTop, itMusicBar->second.defaultRectWidth,itMusicBar->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(soundBar, {false, false, utils::constant::SOUND_BAR});

    world.registry.addComponent<ecs::component::Position>(musicBar, {itMusicBar->second.posX, itMusicBar->second.posY + 200});
    world.registry.addComponent<ecs::component::Size>(musicBar, {itMusicBar->second.rectHeight, itMusicBar->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(musicBar, {"menu", {itMusicBar->second.rectLeft, itMusicBar->second.rectTop, itMusicBar->second.defaultRectWidth,itMusicBar->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(musicBar, {false, false, utils::constant::SOUND_BAR});

    world.registry.addComponent<ecs::component::Position>(slideSoundButton, {itSoundSlide->second.posX, itSoundSlide->second.posY});
    world.registry.addComponent<ecs::component::Size>(slideSoundButton, {itSoundSlide->second.rectHeight, itSoundSlide->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(slideSoundButton, {"menu", {itSoundSlide->second.rectLeft, itSoundSlide->second.rectTop, itSoundSlide->second.defaultRectWidth,itSoundSlide->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(slideSoundButton, {false, false, utils::constant::SLIDE_SOUND});

    world.registry.addComponent<ecs::component::Position>(slideMusicButton, {itMusicSlide->second.posX, itMusicSlide->second.posY});
    world.registry.addComponent<ecs::component::Size>(slideMusicButton, {itMusicSlide->second.rectHeight, itMusicSlide->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(slideMusicButton, {"menu", {itMusicSlide->second.rectLeft, itMusicSlide->second.rectTop, itMusicSlide->second.defaultRectWidth,itMusicSlide->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(slideMusicButton, {false, false, utils::constant::SLIDE_MUSIC});

    world.registry.addComponent<ecs::component::Position>(settingsButton, {itSetting->second.posX, itSetting->second.posY});
    world.registry.addComponent<ecs::component::Size>(settingsButton, {itSetting->second.rectHeight, itSetting->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(settingsButton, {"menu", {itSetting->second.rectLeft, itSetting->second.rectTop, itSetting->second.defaultRectWidth, itSetting->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(settingsButton, {false, true, utils::constant::SETTINGS});

    world.registry.addComponent<ecs::component::Position>(howToPlayButton, {itHowTo->second.posX, itHowTo->second.posY});
    world.registry.addComponent<ecs::component::Size>(howToPlayButton, {itHowTo->second.rectHeight, itHowTo->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(howToPlayButton, {"menu", {itHowTo->second.rectLeft, itHowTo->second.rectTop, itHowTo->second.defaultRectWidth, itHowTo->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(howToPlayButton, {false, true, utils::constant::HOW_TO});
}

static void setOptionInterfaceText(ecs::World &world)
{
    ecs::Entity soundText = world.registry.spawn_entity();
    ecs::Entity musicText = world.registry.spawn_entity();
    ecs::Entity howToPlayText = world.registry.spawn_entity();
    ecs::Entity settingsText = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Text>(soundText, {"Music"});
    world.registry.addComponent<ecs::component::Text>(musicText, {"Sound Effect"});
    world.registry.addComponent<ecs::component::Text>(settingsText, {"Settings"});
    world.registry.addComponent<ecs::component::Text>(howToPlayText, {"How To play"});
    world.registry.addComponent<ecs::component::Position>(soundText, {1095, 302});
    world.registry.addComponent<ecs::component::Position>(musicText, {1055, 502});
    world.registry.addComponent<ecs::component::Position>(howToPlayText, {1190, 660});
    world.registry.addComponent<ecs::component::Position>(settingsText, {935, 660});
    world.registry.addComponent<ecs::component::Size>(soundText, {30, 30});
    world.registry.addComponent<ecs::component::Size>(musicText, {30, 30});
    world.registry.addComponent<ecs::component::Size>(howToPlayText, {30, 30});
    world.registry.addComponent<ecs::component::Size>(settingsText, {30, 30});
    world.registry.addComponent<ecs::component::Activable>(soundText, {false, false, utils::constant::OPTIONS_TEXT});
    world.registry.addComponent<ecs::component::Activable>(musicText, {false, false, utils::constant::OPTIONS_TEXT});
    world.registry.addComponent<ecs::component::Activable>(howToPlayText, {false, false, utils::constant::OPTIONS_TEXT});
    world.registry.addComponent<ecs::component::Activable>(settingsText, {false, false, utils::constant::OPTIONS_TEXT});
}

static void setOptionInterface(ecs::World &world)
{
    auto itOptionInterface = utils::constant::buttonValueMap.find(utils::constant::OPTION_INTERFACE);
    ecs::Entity optionInterface = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(optionInterface, {itOptionInterface->second.posX, itOptionInterface->second.posY});
    world.registry.addComponent<ecs::component::Size>(optionInterface, {itOptionInterface->second.rectHeight, itOptionInterface->second.rectWidth});
    world.registry.addComponent<ecs::component::Drawable>(optionInterface, {"menu", {itOptionInterface->second.rectLeft, itOptionInterface->second.rectTop, itOptionInterface->second.defaultRectWidth, itOptionInterface->second.defaultRectHeight}});
    world.registry.addComponent<ecs::component::Activable>(optionInterface, {false, false, utils::constant::OPTION_INTERFACE});
}

static void setBackgroundTexture(ecs::World &world)
{
    ecs::Entity background = world.registry.spawn_entity();

    world.registry.addComponent<ecs::component::Position>(background, {0, 0});
    world.registry.addComponent<ecs::component::Size>(
            background, {utils::constant::mapHeight, utils::constant::mapWidth});
    world.registry.addComponent<ecs::component::Drawable>(background, {"bgmenu", {0, 0, 6000, 3000}});
    world.registry.addComponent<ecs::component::Activable>(background, {});
}

static void setRoomPlanet(ecs::World &world)
{
    ecs::Entity planet1 = world.registry.spawn_entity();
    ecs::Entity planet2 = world.registry.spawn_entity();
    ecs::Entity planet3 = world.registry.spawn_entity();
    ecs::Entity planet4 = world.registry.spawn_entity();
    int width = 7392;
    int height = 96;
    int nbFrame = 77;
    int delay = 75;

    world.registry.addComponent<ecs::component::Position>(planet1, {1280, 250});
    world.registry.addComponent<ecs::component::Size>(planet1, {height, width / nbFrame});
    world.registry.addComponent<ecs::component::Drawable>(planet1, {"planet", {0, 0, (width / nbFrame), height}});
    world.registry.addComponent<ecs::component::Activable>(planet1, {false, false, utils::constant::PLANET});
    world.registry.addComponent<ecs::component::Animated>(planet1,
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
    world.registry.addComponent<ecs::component::Position>(planet2, {1280, 400});
    world.registry.addComponent<ecs::component::Size>(planet2, {height, width / nbFrame});
    world.registry.addComponent<ecs::component::Drawable>(planet2, {"planet", {0, 0, (width / nbFrame), height}});
    world.registry.addComponent<ecs::component::Activable>(planet2, {false, false, utils::constant::PLANET});
    world.registry.addComponent<ecs::component::Animated>(planet2,
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
    world.registry.addComponent<ecs::component::Position>(planet3, {1280, 550});
    world.registry.addComponent<ecs::component::Size>(planet3, {height, width / nbFrame});
    world.registry.addComponent<ecs::component::Drawable>(planet3, {"planet", {0, 0, (width / nbFrame), height}});
    world.registry.addComponent<ecs::component::Activable>(planet3, {false, false, utils::constant::PLANET});
    world.registry.addComponent<ecs::component::Animated>(planet3,
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
    world.registry.addComponent<ecs::component::Position>(planet4, {1280, 700});
    world.registry.addComponent<ecs::component::Size>(planet4, {height, width / nbFrame});
    world.registry.addComponent<ecs::component::Drawable>(planet4, {"planet", {0, 0, (width / nbFrame), height}});
    world.registry.addComponent<ecs::component::Activable>(planet4, {false, false, utils::constant::PLANET});
    world.registry.addComponent<ecs::component::Animated>(planet4,
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

static void setMenuBackground(ecs::World &world)
{
    setBackgroundTexture(world);
    setMainButtons(world);
    setRoomButtons(world);
    setRoomTexts(world);
    setRoomPlanet(world);
    setOptionInterface(world);
    setVolumeButtons(world);
    setOptionInterfaceText(world);
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
    setMenuBackground(world);
    return world;
}

#pragma endregion MenuWorld