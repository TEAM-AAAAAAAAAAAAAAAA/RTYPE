/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Server
*/

#include "AssetLoader.hpp"
#include <filesystem>

namespace asset
{
    AssetLoader AssetLoader::_Instance;

    AssetLoader::~AssetLoader() {}

    void AssetLoader::LoadAsset(const std::filesystem::path &path)
    {
        sf::Texture texture;

        if (!texture.loadFromFile(path))
            return;
        _Instance._assetsMap[path] = texture;
    }

    sf::Texture &AssetLoader::GetAsset(const std::filesystem::path &path)
    {
        return _Instance._assetsMap[path];
    }

} // namespace asset