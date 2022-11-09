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

/**
 * Main function of the client, running everything to start the game
 * @return 0 if no error, anything otherwise
 */
int main()
{
    asset::AssetLoader::LoadIniFile(asset::AssetLoader::smartPath("assets", "config.ini"));
	audio::AudioManager::playSFX("startup");
	audio::AudioManager::loadBGM("roll");
	audio::AudioManager::playBGM(true);
    utils::Window::getInstance().setFramerateLimit(60);
    ecs::Engine engine;
    // ecs::WorldManager::setWaitingWorld(getMenuWorld);
    ecs::WorldManager::setWaitingWorld(getGameWorld);

    engine.run();
    return 0;
}
