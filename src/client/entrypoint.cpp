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

/**
 * Main function of the client, running everything to start the game
 * @return 0 if no error, anything otherwise
 */
int main()
{
    ecs::Engine engine;
    asset::AssetLoader::LoadIniFile(asset::AssetLoader::smartPath("assets", "config.ini"));
    audio::AudioManager::playSFX("splash_screen");
    audio::AudioManager::loadBGM("bgm1");
    audio::AudioManager::playBGM(true);
    ecs::WorldManager::setWaitingWorld(getMenuWorld);
    engine.run();
    return 0;
}
