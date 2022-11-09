/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#include "AssetLoader.hpp"
#include "Engine.hpp"
#include "GetWorld.hpp"
#include "AudioManager.hpp"
#include "NetworkClient.hpp"

/**
 * Main function of the client, running everything to start the game
 * @return 0 if no error, anything otherwise
 */
int main()
{
    asset::AssetLoader::LoadIniFile(asset::AssetLoader::smartPath("assets", "config.ini"));

    audio::AudioManager::playSFX("splash_screen");
    audio::AudioManager::loadBGM("bgm1");
    audio::AudioManager::playBGM(true);
    network::Client::setHost("localhost");
    network::Client::setPort("8000");
    network::Client::connect();
    utils::Window::getInstance().setFramerateLimit(60);
    ecs::Engine engine;
    // ecs::WorldManager::setWaitingWorld(getMenuWorld);
    ecs::WorldManager::setWaitingWorld(getGameWorld);

    engine.run();
    return 0;
}
