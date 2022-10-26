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

    void AssetLoader::LoadTexture(const std::string &key, const std::filesystem::path &path)
    {
        sf::Texture texture;

        if (!texture.loadFromFile(path.generic_string()))
            return;
        _Instance._textureMap[key] = texture;
    }

    sf::Texture &AssetLoader::GetTexture(const std::string &key) { return _Instance._textureMap[key]; }

} // namespace asset