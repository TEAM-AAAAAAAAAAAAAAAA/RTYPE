/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#include "AssetLoader.hpp"
#include "AudioManager.hpp"
#include "Engine.hpp"
#include "GetWorld.hpp"
#include "LockedQueue.hpp"
#include "NetworkClient.hpp"

/**
 * Main function of the client, running everything to start the game
 * @return 0 if no error, anything otherwise
 */
int main()
{
    ecs::Engine engine;
    network::Message msg;

    network::Client::setHost("localhost");
    network::Client::setPort("8000");
    msg.fill(0);
    network::Client::connect();
    network::Client::getOutgoingMessages().push(msg);
    asset::AssetLoader::LoadIniFile(asset::AssetLoader::smartPath("assets", "config.ini"));
    audio::AudioManager::playSFX("splash_screen");
    ecs::WorldManager::setWaitingWorld(getMenuWorld);
    audio::AudioManager::setBGMVolume(0);
    audio::AudioManager::setSFXVolume(50);
    engine.run();
    return 0;
}
