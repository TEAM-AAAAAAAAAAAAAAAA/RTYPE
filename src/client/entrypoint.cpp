/*
** EPITECH PROJECT, by hourcadettej on 10/3/22.
** rtype
** File description:
** rtype
*/

#include "AssetLoader.hpp"
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
    ecs::WorldManager::setWaitingWorld(getMenuWorld);
//    ecs::WorldManager::setWaitingWorld([] { return getGameWorld("8000", "localhost"); });
    engine.run();
    return 0;
}
